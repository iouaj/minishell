/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:21:30 by souaguen          #+#    #+#             */
/*   Updated: 2024/03/28 15:05:31 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void	read_list(t_list *lst)
{
	t_list	*cursor;
	t_token	*token;

	cursor = lst;
	while (cursor != NULL)
	{
		token = (t_token *)(*cursor).content;
		printf("TOKEN: \"%s\"\nQUOTED: %d\n\n", (*token).str, (*token).quoted);
		cursor = (*cursor).next;
	}
}

t_list	*get_new_pipe(t_list **lst)
{
	t_token	*token;
	t_list	*cursor;
	t_list	*new;

	new = NULL;
	cursor = *lst;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if ((*token).quoted == 0 && !ft_strncmp((*token).str, "|", 2))
		{
			*lst = (*cursor).next;
			return (new);
		}
		ft_lstadd_back(&new, ft_lstnew(token));
		cursor = (*cursor).next;
	}
	*lst = NULL;
	return (new);
}

void	free_lst(t_list *lst)
{
	t_list	*cursor;
	t_list	*tmp;

	cursor = lst;
	while (cursor != NULL)
	{
		tmp = (*cursor).next;
		free(cursor);
		cursor = tmp;
	}
}

char	**lst_to_argv(t_list *lst)
{
	t_token	*token;
	t_list	*cursor;
	t_list	*new;
	char	**argv;
	char	*tmp;
	int		siz;

	siz = 0;
	new = NULL;
	argv = NULL;
	cursor = lst;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if (!ft_strncmp((*token).str, "<", 2) || !ft_strncmp((*token).str, ">", 2))
			break ;
		else if (!((*token).quoted == 0 && !ft_strncmp((*token).str, " ", 2)))
		{
			while (cursor != NULL)
			{
				if ((*cursor).next != NULL
					&& ft_strncmp((*(t_token *)(*(*cursor).next).content).str, " ", 2)
					&& ft_strncmp((*(t_token *)(*(*cursor).next).content).str, ">", 2)
					&& ft_strncmp((*(t_token *)(*(*cursor).next).content).str, "<", 2)
					&& ft_strncmp((*(t_token *)(*(*cursor).next).content).str, "|", 2))
				{
					tmp = (*token).str;
					(*token).str = ft_strjoin((*token).str, (*(t_token *)(*(*cursor).next).content).str);
					free(tmp);
					cursor = (*cursor).next;
				}
				else
					break ;
			}
			ft_lstadd_back(&new, ft_lstnew(token));
		}
		if (cursor == NULL)
			break ;
		cursor = (*cursor).next;
	}
	siz = ft_lstsize(new);
	argv = malloc(sizeof(char *) * (siz + 1));
	if (argv == NULL)
		return (NULL);
	argv[siz] = NULL;
	siz = 0;
	cursor = new;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		argv[siz] = (*token).str;
		cursor = (*cursor).next;
		siz++;
	}
	free_lst(new);
	return (argv);
}

void	read_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		printf("%s\n", argv[i]);
		i++;
	}
	printf("\n");
	// free(argv);
}

int	main(int argc, char **argv, char *envp[])
{
	t_pipeline	*pipln;
	t_list		*pipeline;
	t_list		*lst;
	t_list		*parsed;
	t_list		*backup;
	t_list		*new;
	char		*str;
	t_env		*e;

	pipeline = NULL;
	if (argc != 2)
		return (1);
	lst = parsing_init(argv[1]);
	parsed = ft_lstmap(lst, ft_env, free);
	backup = parsed;
	while (parsed != NULL)
	{
		new = get_new_pipe(&parsed);
		printf("NEW_PIPELINE\n\n");
		//read_list(new);
		pipln = malloc(sizeof(t_pipeline));
		(*pipln).argv = lst_to_argv(new);
		(*pipln).fd_in = 0;
		(*pipln).fd_out = 1;
		(*pipln).eof = NULL;
		(*pipln).exit_code = 0;
		ft_lstadd_back(&pipeline, ft_lstnew(pipln));
		read_argv((*pipln).argv);
		free_lst(new);
	}
	e = get_env_list(envp);
	printf("Getting env\n");
	// Run exec with linked list (t_list *pipeline) here
	while (pipeline)
	{
		exec(pipeline, &e, envp);
		pipeline = pipeline->next;
	}
	// run(pipeline);
	//
	ft_lstclear(&lst, &free_quoted);
	ft_lstclear(&backup, &free_quoted);
	return (0);
}

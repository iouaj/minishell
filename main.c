/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:21:30 by souaguen          #+#    #+#             */
/*   Updated: 2024/04/01 14:09:11 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

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

int	pipe_create(char *input, char *envp[], t_env **e)
{
	t_pipeline	*pipln;
	t_list		*pipeline;
	t_list		*lst;
	t_list		*parsed;
	t_list		*backup;
	t_list		*new;
	int	value;

	pipeline = NULL;
	lst = parsing_init(input);
	parsed = ft_lstmap(lst, ft_env, free);
	backup = parsed;
	while (parsed != NULL)
	{
		new = get_new_pipe(&parsed);
		pipln = malloc(sizeof(t_pipeline));
		(*pipln).argv = lst_to_argv(new);
		(*pipln).fd_in = 0;
		(*pipln).fd_out = 1;
		(*pipln).eof = NULL;
		(*pipln).exit_code = 0;
		ft_lstadd_back(&pipeline, ft_lstnew(pipln));
		free_lst(new);
	}
	value = run(pipeline, e, envp);
	// printf("%d\n", value);
	// set_error(e, value);
	ft_lstclear(&lst, &free_quoted);
	ft_lstclear(&backup, &free_quoted);
	ft_lstclear(&pipeline, &free_pipeline);
	return (value);
}

int	main(int argc, char *argv[], char *envp[])
{
	char				*str;
	t_env	*e;

	(void) argc;
	(void) argv;
	str = NULL;
	e = get_env_list(envp);
	if (!e)
	{
		perror("malloc");
		return (1);
	}
	while (1)
	{
		if (str)
			free(str);
		str = readline("\033[1;34mminishell$> \033[0m");
		if (str && str[0])
		{
			add_history(str);
			if (pipe_create(str, envp, &e) == EXIT_FAILURE)
				break ;
		}
	}
	printf("\n\ngoodbye\n");
	clear_history();
	free(str);
	free_env(e);
	return (0);
}

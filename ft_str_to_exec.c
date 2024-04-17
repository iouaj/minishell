/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:26:46 by souaguen          #+#    #+#             */
/*   Updated: 2024/04/17 13:05:11 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_next_pipe(t_list **lst)
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

void	ft_skip_cursor(t_list **lst, t_token **token)
{
	t_list	*cursor;
	char	*str;
	char	*tmp;

	cursor = *lst;
	while (cursor != NULL)
	{
		if ((*cursor).next != NULL
			&& ft_strncmp((*(t_token *)(*(*cursor).next).content).str, " ", 2)
			&& ft_strncmp((*(t_token *)(*(*cursor).next).content).str, ">", 2)
			&& ft_strncmp((*(t_token *)(*(*cursor).next).content).str, "<", 2)
			&& ft_strncmp((*(t_token *)(*(*cursor).next).content).str, "|", 2))
		{
			tmp = (**token).str;
			str = (*(t_token *)(*(*cursor).next).content).str;
			(**token).str = ft_strjoin((**token).str, str);
			free(tmp);
			cursor = (*cursor).next;
		}
		else
			break ;
	}
	*lst = cursor;
}

char	**ft_convert_list(t_list *lst)
{
	t_token	*token;
	t_list	*cursor;
	char	**argv;
	int		siz;

	siz = ft_lstsize(lst);
	argv = malloc(sizeof(char *) * (siz + 1));
	if (argv == NULL)
		return (NULL);
	argv[siz] = NULL;
	siz = 0;
	cursor = lst;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		argv[siz] = (*token).str;
		cursor = (*cursor).next;
		siz++;
	}
	free_lst(lst);
	return (argv);
}

char	**lst_to_argv(t_list *lst)
{
	t_token	*token;
	t_list	*cursor;
	t_list	*new;

	new = NULL;
	cursor = lst;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if (!ft_strncmp((*token).str, "<", 2)
			|| !ft_strncmp((*token).str, ">", 2))
			break ;
		else if (!((*token).quoted == 0 && !ft_strncmp((*token).str, " ", 2)))
		{
			ft_skip_cursor(&cursor, &token);
			ft_lstadd_back(&new, ft_lstnew(token));
		}
		if (cursor == NULL)
			break ;
		cursor = (*cursor).next;
	}
	return (ft_convert_list(new));
}

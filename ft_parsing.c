/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:35:43 by souaguen          #+#    #+#             */
/*   Updated: 2024/04/17 13:05:05 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	*update_line(void *content)
{
	t_token	*token;
	char	*tmp;
	char	*str;

	str = (char *)content;
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	tmp = str;
	(*token).quoted = 0;
	if (*(str) == '\'' && ft_strchr((str + 1), '\''))
	{
		(*token).quoted = 1;
		tmp = ft_strtrim(str, "\'");
	}
	else if (*(str) == '\"' && ft_strchr((str + 1), '\"'))
	{
		(*token).quoted = 2;
		tmp = ft_strtrim(str, "\"");
	}
	(*token).str = tmp;
	if ((*token).quoted == 0)
		(*token).str = ft_strdup(tmp);
	return ((void *)token);
}

void	free_quoted(void *ptr)
{
	t_token	*token;

	token = ptr;
	if (token != NULL)
	{
		free((*token).str);
		(*token).str = NULL;
		free(ptr);
		ptr = NULL;
	}
}

t_list	*parsing_init(char *cmd)
{
	t_list	*lst;
	t_list	*swp;
	char	*token;
	char	*backup;
	char	*str;

	str = ft_strdup(cmd);
	backup = str;
	lst = NULL;
	if (str == NULL)
		return (NULL);
	token = ft_strtok(&str, " ><|");
	while (token)
	{
		ft_lstadd_back(&lst, ft_lstnew(token));
		token = ft_strtok(&str, " ><|");
	}
	swp = ft_lstmap(lst, &update_line, &free);
	ft_lstclear(&lst, free);
	free(backup);
	return (swp);
}

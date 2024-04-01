/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:03:31 by souaguen          #+#    #+#             */
/*   Updated: 2024/04/01 15:12:56 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_something(char *content)
{
	char	*env;

	if (*(content) != '$')
		return (content);
	env = getenv(content + 1);
	if (env != NULL)
		return (env);
	return ("");
}

char	*ft_lstto_str(t_list **lst)
{
	t_list	*cursor;
	char	*str;
	char	*tmp;

	cursor = *lst;
	str = ft_strdup("");
	while (cursor != NULL)
	{
		tmp = str;
		str = ft_strjoin(str, ft_something((*cursor).content));
		free(tmp);
		cursor = (*cursor).next;
	}
	ft_lstclear(lst, free);
	return (str);
}

char	*ft_replace_env(char *str)
{
	t_list	*lst;
	char	backup;
	int		i;
	int		start;

	i = 0;
	start = 0;
	lst = NULL;
	while (*(char *)(str + i) != '\0')
	{
		if (ft_strchr(" $", *(char *)(str + i)) != NULL)
		{
			backup = *(char *)(str + i);
			*(char *)(str + i) = '\0';
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(str + start)));
			*(char *)(str + i) = backup;
			start = i;
		}
		i++;
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup(str + start)));
	return (ft_lstto_str(&lst));
}

void	*ft_env(void *content)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	(*token).str = ft_replace_env((*(t_token *)content).str);
	(*token).quoted = (*(t_token *)content).quoted;
	return (token);
}

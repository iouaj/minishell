/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:21:30 by souaguen          #+#    #+#             */
/*   Updated: 2024/03/27 18:20:48 by iouajjou         ###   ########.fr       */
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

int	main(int argc, char **argv, char *envp[])
{
	t_list	*lst;
	t_list	*parsed;
	char	*str;
	t_env	*e;

	// if (argc != 2)
	// 	return (1);
	(void) argc;
	(void) argv;

	e = get_env_list(envp);
	if (!e)
		return (printf("error env\n"));
	while (1)
	{
		str = readline("\033[1;34mminishell$> \033[0m");
		lst = parsing_init(str);
		parsed = ft_lstmap(lst, ft_env, free);
		//read_list(parsed);
		if (!exec(parsed, &e, envp))
			break ;
	}
	free_env(e);
	ft_lstclear(&lst, &free_quoted);
	ft_lstclear(&parsed, &free_quoted);
	return (0);
}

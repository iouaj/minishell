/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:44:40 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/21 16:59:46 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go(const char *str)
{
	if (!str || str[0] == 0)
		return (1);
	return (ft_strncmp(str, "exit", ft_strlen(str)));
}

void	settermios(struct termios old_term)
{
	struct termios	new_term;

	new_term = old_term;
	new_term.c_cc[VINTR] = 4;
	new_term.c_cc[VEOF] = 3;
	new_term.c_cc[VERASE] = 0;
	tcsetattr(0, TCSANOW, &new_term);
}

void	parsing(char *str)
{
	if (!ft_strncmp(str, "exit", 4))
		return ;
	else
		printf("%s: command not found\n", str);
}

int	main(void)
{
	char				*str;
	struct termios		old_term;

	str = NULL;
	tcgetattr(0, &old_term);
	settermios(old_term);
	while (go(str))
	{
		if (str)
			free(str);
		str = readline("$>");
		if (str && str[0])
		{
			parsing(str);
			add_history(str);
		}
	}
	clear_history();
	free(str);
	tcsetattr(0, TCSANOW, &old_term);
	return (0);
}

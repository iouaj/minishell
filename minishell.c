/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:44:40 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/25 14:12:05 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



//Change termios
//Ctrl D will now exit minishell, Ctrl C create a newline and Ctrl \ will do nothing.
void	settermios(struct termios old_term)
{
	struct termios	new_term;

	new_term = old_term;
	new_term.c_cc[VINTR] = 4;
	new_term.c_cc[VEOF] = 3;
	new_term.c_cc[VQUIT] = 0;
	tcsetattr(0, TCSANOW, &new_term);
}

int	main(void)
{
	char				*str;
	struct termios		old_term;
	t_env	*env;

	str = NULL;
	env = get_env_list();
	if (!env)
	{
		printf("Malloc error\n");
		return (1);
	}
	tcgetattr(0, &old_term);
	settermios(old_term);
	while (1)
	{
		if (str)
			free(str);
		str = readline("$>");
		if (str && str[0])
		{
			add_history(str);
			if (!parsing(str, &env))
			break ;
		}
	}
	clear_history();
	free(str);
	free(env);
	tcsetattr(0, TCSANOW, &old_term);
	return (0);
}

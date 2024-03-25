/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:44:40 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/25 16:37:02 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig = 1;

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

// void	handle_sigusr(int sig, siginfo_t *siginfo, void *context)
// {
// 	(void) sig;
// 	(void) siginfo;
// 	(void) context;
// 	printf("yo\n");
// 	g_sig = 0;
// }

// void	setsignal(void)
// {
// 	struct sigaction	sa;

// 	sa.sa_flags = SA_SIGINFO;
// 	sa.sa_sigaction = handle_sigusr;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// }

int	main(int argc, char *argv[], char *envp[])
{
	char				*str;
	struct termios		old_term;
	t_env	*env;

	(void) argc;
	(void) argv;
	str = NULL;
	env = get_env_list(envp);
	if (!env)
	{
		printf("Malloc error\n");
		return (1);
	}
	tcgetattr(0, &old_term);
	settermios(old_term);
	// setsignal();
	while (g_sig)
	{
		if (str)
			free(str);
		str = readline("$>");
		if (str && str[0])
		{
			add_history(str);
			if (!parsing(str, &env, envp))
				break ;
		}
	}
	printf("yo\n");
	clear_history();
	free(str);
	free(env);
	tcsetattr(0, TCSANOW, &old_term);
	return (0);
}

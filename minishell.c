/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:44:40 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/20 17:54:39 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go(const char *str)
{
	if (!str)
	{
		return (1);
	}
	return (ft_strncmp(str, "exit", ft_strlen(str)));
}

void	handle_sigusr(int sig, siginfo_t *siginfo, void *context)
{
	(void) context;
	(void) siginfo;
	if (sig == SIGINT)
	{
		rl_on_new_line();
	}
}

int main(void)
{
	char				*str;
	struct sigaction	sa;

	str = NULL;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_sigusr;
	sigemptyset(&sa.sa_mask);
	// sigaction(SIGINT, &sa, NULL);
	while (go(str))
	{
		if (str)
			free(str);
		str = readline("$>");
		if (go(str))
		{
			add_history(str);
		}
	}
	clear_history();
	free(str);
	return (0);
}

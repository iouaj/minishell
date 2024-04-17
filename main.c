/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:21:30 by souaguen          #+#    #+#             */
/*   Updated: 2024/04/17 15:39:28 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

int	g_sig = 0;

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
	free(argv);
}

int	ft_exec_pipeline(char *entry, char **envp, t_env **e, t_sys *sys)
{
	t_list	*lst;
	t_list	*parsed;
	t_list	*backup;
	t_list	*pipeline;
	int		fd;

	lst = parsing_init(entry);
	parsed = ft_lstmap(lst, ft_env, free);
	backup = parsed;
	pipeline = ft_pipeline_init(parsed);
	fd = dup(0);
	dup2((*(t_pipeline *)(*pipeline).content).fd_in, 0);
	((t_pipeline *)pipeline->content)->exit_code = run(pipeline, e, envp, sys);
	dup2(fd, 0);
	close(fd);
	ft_lstclear(&lst, &free_quoted);
	ft_lstclear(&backup, &free_quoted);
	return (((t_pipeline *)pipeline->content)->exit_code);
}

//Change termios
//Ctrl D will now exit minishell,
//Ctrl C create a newline and Ctrl \ will do nothing.
int	settermios(struct termios old_term)
{
	struct termios	new_term;

	new_term = old_term;
	new_term.c_cc[VINTR] = 4;
	new_term.c_cc[VEOF] = 3;
	new_term.c_cc[VQUIT] = 0;
	tcsetattr(0, TCSANOW, &new_term);
	return (tcgetattr(0, &new_term));
}

void	handle_sigusr(int sig, siginfo_t *siginfo, void *context)
{
	(void) context;
	g_sig = sig;
	if (close(siginfo->si_fd) == -1)
		exit(error("close", ERR_G));
}

int	setsignal(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handle_sigusr;
	if (sigemptyset(&sa.sa_mask) == -1)
		return (-1);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (-1);
	return (0);
}

struct	termios	setup(t_env *e)
{
	struct termios	old_term;

	if (tcgetattr(0, &old_term) == -1)
	{
		free_env(e);
		exit(error("tcgetattr", ERR_G));
	}
	if (settermios(old_term) == -1)
	{
		free_env(e);
		exit(error("tcsetattr", ERR_G));
	}
	if (setsignal() == -1)
	{
		free_env(e);
		exit(error("signal", ERR_G));
	}
	return (old_term);
}

void	end_shell(char *str, t_env *e, struct termios old_term)
{
	clear_history();
	free(str);
	free_env(e);
	tcsetattr(0, TCSANOW, &old_term);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_sys	sys;
	int		exit_code;

	(void) argc;
	(void) argv;
	sys.input = NULL;
	exit_code = 0;
	sys.e = get_env_list(envp);
	if (!sys.e)
		exit(error("malloc", ERR_MEM));
	sys.old_term = setup(sys.e);
	while (g_sig != SIGINT)
	{
		free(sys.input);
		sys.input = readline("\033[1;34mminishell$> \033[0m");
		if (sys.input && sys.input[0])
		{
			add_history(sys.input);
			sys.pipe = 0;
			exit_code = ft_exec_pipeline(sys.input, envp, &sys.e, &sys);
		}
		printf("%d\n", exit_code);
	}
	end_shell(sys.input, sys.e, sys.old_term);
	return (0);
}

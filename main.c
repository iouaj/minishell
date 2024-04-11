/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:21:30 by souaguen          #+#    #+#             */
/*   Updated: 2024/04/11 15:22:56 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

int g_sig = 0;

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

int	pipe_create(char *input, char *envp[], t_env **e, t_sys *sys)
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
	value = run(pipeline, e, envp, sys);
	ft_lstclear(&lst, &free_quoted);
	ft_lstclear(&backup, &free_quoted);
	ft_lstclear(&pipeline, &free_pipeline);
	return (value);
}

//Change termios
//Ctrl D will now exit minishell, Ctrl C create a newline and Ctrl \ will do nothing.
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
			exit_code = pipe_create(sys.input, envp, &sys.e, &sys);
		}
		printf("%d\n", exit_code);
	}
	end_shell(sys.input, sys.e, sys.old_term);
	return (0);
}

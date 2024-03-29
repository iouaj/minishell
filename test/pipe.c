/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:23:18 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/29 17:51:45 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_file(int fd_to_read, int fd_to_write)
{
	int		i;
	char	buf;

	while (read(fd_to_read, &buf, 1) > 0)
		ft_putchar_fd(buf, fd_to_write);
}

int	checkcmd(t_list *cmds, t_env **e)
{
	t_pipeline	*pipe;
	int			i;
	int			exit_value;

	pipe = (t_pipeline *) cmds->content;
	exit_value = -1;
	if (!ft_strncmp(pipe->argv[0], "export", ft_strlen(pipe->argv[0])))
		exit_value = export(e, pipe, 1);
	else if (!ft_strncmp(pipe->argv[0], "unset", ft_strlen(pipe->argv[0])))
	{
		i = 1;
		while (pipe->argv[i] && exit_value != EXIT_FAILURE)
		{
			exit_value = env_delete(e, pipe->argv[i]);
			i++;
		}
	}
	return (exit_value);
}

int	child_process(t_list *cmds, t_env **e, char *envp[], int pipefd[2])
{
	int	fd;
	int	exit_value;
	t_pipeline	*pipe;

	pipe = (t_pipeline *) cmds->content;
	close(pipefd[0]);
	fd = dup(pipe->fd_out);
	dup2(pipefd[1], pipe->fd_out);
	exit_value = exec(cmds, e, envp);
	dup2(fd, pipe->fd_out);
	close(pipefd[1]);
	close(fd);
	exit(exit_value);
}

int	parent_process(t_list *cmds, t_env **e, char *envp[], int pipefd[])
{
	int	fd;
	int	wstatus;
	t_pipeline	*pipe;

	pipe = (t_pipeline *) cmds->content;
	close(pipefd[1]);
	if (cmds != NULL && (*cmds).next != NULL)
	{
		fd = dup(pipe->fd_in);
		dup2(pipefd[0], pipe->fd_in);
		run((*cmds).next, e, envp);
		dup2(fd, pipe->fd_in);
		close(fd);
	}
	else
		read_file(pipefd[0], pipe->fd_out);
	close(pipefd[0]);
	waitpid(-1, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}

int	run(t_list *cmds, t_env **e, char *envp[])
{
	pid_t		pid;
	int			pipefd[2];
	int			wstatus;
	int			fd;
	int			exit_value;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if (checkcmd(cmds, e) != -1)
		return (EXIT_SUCCESS);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		return (child_process(cmds, e, envp, pipefd));
	else
		return (parent_process(cmds, e, envp, pipefd));
}

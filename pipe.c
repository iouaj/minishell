/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:23:18 by iouajjou          #+#    #+#             */
/*   Updated: 2024/04/10 15:00:12 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_file(int fd_to_read, int fd_to_write)
{
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
	else if (!ft_strncmp(pipe->argv[0], "cd", ft_strlen(pipe->argv[0])))
		exit_value = cd(pipe, *e);
	errno = exit_value;
	return (exit_value);
}

int	child_process(t_list *cmds, t_env **e, char *envp[], int pipefd[2])
{
	int	fd;
	int	exit_value;
	t_pipeline	*pipe;

	pipe = (t_pipeline *) cmds->content;
	if (close(pipefd[0]) == -1)
		exit(error("close"));
	fd = dup(pipe->fd_out);
	if (fd == -1)
		exit(error("dup"));
	if (dup2(pipefd[1], pipe->fd_out) == -1)
		exit(error("dup2"));
	exit_value = exec(cmds, e, envp);
	if (dup2(fd, pipe->fd_out) == -1)
		exit(error("dup2"));
	if (close(pipefd[1]) == -1)
		exit(error("close"));
	if (close(fd) == -1)
		exit(error("close"));
	exit(exit_value);
}

int	parent_process(t_list *cmds, t_env **e, char *envp[], int pipefd[])
{
	int	fd;
	int	wstatus;
	t_pipeline	*pipe;

	pipe = (t_pipeline *) cmds->content;
	if (close(pipefd[1]) == -1)
		exit(error("close"));
	if (cmds != NULL && (*cmds).next != NULL)
	{
		fd = dup(pipe->fd_in);
		if (!fd)
			exit(error("dup"));
		if (dup2(pipefd[0], pipe->fd_in) == -1)
			exit(error("dup2"));
		run((*cmds).next, e, envp);
		if (dup2(fd, pipe->fd_in) == -1);
			exit(error("dup2"));
		if (close(fd) == -1)
			exit(error("close"));
	}
	else
		read_file(pipefd[0], pipe->fd_out);
	if (close(pipefd[0]) == -1)
		exit(error("close"));
	if (waitpid(-1, &wstatus, 0) == -1)
		exit(erro("waitpid"));
	return (WEXITSTATUS(wstatus));
}

int	run(t_list *cmds, t_env **e, char *envp[])
{
	pid_t		pid;
	int			pipefd[2];

	if (pipe(pipefd) == -1)
	{
		exit(error("pipe"));
	}
	if (checkcmd(cmds, e) != -1)
		return (errno);
	pid = fork();
	if (pid < 0)
		return (error("fork"));
	else if (pid == 0)
		return (child_process(cmds, e, envp, pipefd));
	else
		return (parent_process(cmds, e, envp, pipefd));
}

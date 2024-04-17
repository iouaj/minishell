/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:23:18 by iouajjou          #+#    #+#             */
/*   Updated: 2024/04/17 15:41:54 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	read_file(int fd_to_read, int fd_to_write)
// {
// 	char	buf;

// 	while (read(fd_to_read, &buf, 1) > 0)
// 		ft_putchar_fd(buf, fd_to_write);
// }

int	checkcmd(t_list *cmds, t_env **e, t_sys *sys)
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
	else if (!ft_strncmp(pipe->argv[0], "exit", ft_strlen(pipe->argv[0])))
	{
		if (sys->pipe == 1)
		{
			end_shell(NULL, *e, sys->old_term);
			exit(0);
		}
		exit_value = 0;
	}
	return (exit_value);
}

int	child_process(t_pipeline *pip, t_env **e, char *envp[], int pipefd[2])
{
	int	fd;
	int	exit_code;

	if (close(pipefd[0]) == -1)
		return (error("close", ERR_G));
	fd = dup(1);
	if (!fd)
		return (error("dup", ERR_G));
	if ((*pip).fd_out != 1)
	{
		if (dup2((*pip).fd_out, 1) == -1)
			return (error("dup2", ERR_G));
	}
	else
	{
		if (dup2(pipefd[1], 1) == -1)
			return (error("dup2", ERR_G));
	}
	exit_code = exec(pip, e, envp);
	if (dup2(fd, 1) == -1)
		return (error("dup2", ERR_G));
	if (close(pipefd[1]) == -1 || close(fd) == -1)
		return (error("close", ERR_G));
	if ((*pip).fd_out != 1)
	{
		if (close((*pip).fd_out) == -1)
			return (error("close", ERR_G));
	}
	if ((*pip).fd_in != 0)
	{
		if (close((*pip).fd_in) == -1)
			return (error("close", ERR_G));
	}
	exit(exit_code);
}

int	next_pipe(t_list *cmds, t_env **e, char *envp[], int pipefd[], t_sys *sys)
{
	int			fd;
	t_pipeline	*pipe;

	fd = dup(0);
	if (!fd)
		return (error("dup", ERR_G));
	pipe = (t_pipeline *)(*(*cmds).next).content;
	if (pipe->fd_in != 0)
	{
		if (dup2(pipe->fd_in, 0) == -1)
			return (error("dup2", ERR_G));
	}
	else
	{
		if (dup2(pipefd[0], 0) == -1)
			return (error("dup2", ERR_G));
	}
	run((*cmds).next, e, envp, sys);
	if (dup2(fd, 0) == -1)
		return (error("dup2", ERR_G));
	if (close(fd) == -1)
		return (error("close", ERR_G));
	return (0);
}

int	parent_process(t_list *cmds, t_env **e, char *envp[], int pipefd[], t_sys *sys)
{
	int			wstatus;
	t_pipeline	*pipe;

	pipe = (t_pipeline *) cmds->content;
	if (close(pipefd[1]) == -1)
		return (error("close", ERR_G));
	if (cmds != NULL && (*cmds).next != NULL)
	{
		wstatus = next_pipe(cmds, e, envp, pipefd, sys);
		if (wstatus != 0)
			return (wstatus);
	}
	else
		read_file(pipefd[0], pipe->fd_out);
	if (close(pipefd[0]) == -1)
		return (error("close", ERR_G));
	if (waitpid(-1, &wstatus, 0) == -1)
	{
		if (errno == EINTR)
			return (error("waitpid", 128 + WTERMSIG(wstatus)));
		return (error("waitpid", ERR_G));
	}
	return (WEXITSTATUS(wstatus));
}

int	last_pipe(t_pipeline *pip, char *envp[], int pipefd[2], t_env **e)
{
	int	exit_code;

	pipefd[0] = dup(0);
	pipefd[1] = dup(1);
	if ((*pip).fd_in != 0)
		dup2((*pip).fd_in, 0);
	if ((*pip).fd_out != 1)
		dup2((*pip).fd_out, 1);
	exit_code = exec(pip, e, envp);
	dup2(pipefd[0], 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	close(pipefd[1]);
	if ((*pip).fd_out != 1)
		close((*pip).fd_out);
	if ((*pip).fd_in != 0)
		close((*pip).fd_in);
	return (exit_code);
}

void	open_fd(t_pipeline *pip)
{
	if (pip->file_out != NULL)
	{
		if (pip->a_mode)
			pip->fd_out = open(pip->file_out, O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			(*pip).fd_out = open(pip->file_out, O_RDWR | O_CREAT, 0644);
	}
	if (pip->file_in != NULL)
		pip->fd_in = open(pip->file_in, O_RDONLY);
}

int	run(t_list *cmds, t_env **e, char *envp[], t_sys *sys)
{
	pid_t		pid;
	int			pipefd[2];
	int			exit_code;
	t_pipeline	*pip;

	sys->pipe++;
	pip = (t_pipeline *)(*cmds).content;
	open_fd(pip);
	exit_code = checkcmd(cmds, e, sys);
	if (exit_code != -1)
		return (exit_code);
	if (cmds != NULL && (*cmds).next == NULL)
		return (last_pipe(pip, envp, pipefd, e));
	if (pipe(pipefd) == -1)
		return (error("pipe", ERR_G));
	pid = fork();
	if (pid < 0)
		return (error("fork", ERR_G));
	else if (pid == 0)
		return (child_process(pip, e, envp, pipefd));
	else
		return (parent_process(cmds, e, envp, pipefd, sys));
}

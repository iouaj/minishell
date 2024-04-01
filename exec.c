/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:23:58 by iouajjou          #+#    #+#             */
/*   Updated: 2024/04/01 15:24:05 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_execve(t_pipeline *pipe, char *envp[])
{
	char	*path;

	if (!ft_strncmp(pipe->argv[0], "./", 2))
	{
		if (execve(pipe->argv[0], pipe->argv, envp) == -1)
			error("execve");
	}
	else
	{
		path = ft_strjoin("/bin/", pipe->argv[0]);
		if (execve(path, pipe->argv, envp) == -1)
			error("execve");
		free(path);
	}
	exit(errno);
}

int	exec_others(t_pipeline *pipe, char *envp[])
{
	int		pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
		return (0);
	else if (!pid)
		child_execve(pipe, envp);
	else
		waitpid(pid, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}

int	exec(t_list *cmd, t_env **e, char *envp[])
{
	t_pipeline	*pipe;

	pipe = NULL;
	if (cmd)
		pipe = (t_pipeline *)(*cmd).content;
	if (!ft_strncmp(pipe->argv[0], "pwd", ft_strlen(pipe->argv[0])))
		pipe->exit_code = pwd();
	else if (!ft_strncmp(pipe->argv[0], "cd", ft_strlen(pipe->argv[0])))
		pipe->exit_code = cd(pipe, *e);
	else if (!ft_strncmp(pipe->argv[0], "echo", ft_strlen(pipe->argv[0])))
		pipe->exit_code = echo(pipe);
	else if (!ft_strncmp(pipe->argv[0], "exit", ft_strlen(pipe->argv[0])))
		pipe->exit_code = EXIT_FAILURE;
	else if (!ft_strncmp(pipe->argv[0], "env", ft_strlen(pipe->argv[0])))
		pipe->exit_code = env(*e);
	else if (!ft_strncmp(pipe->argv[0], "export", ft_strlen(pipe->argv[0])))
		pipe->exit_code = export(e, pipe, 1);
	else if (!ft_strncmp(pipe->argv[0], "unset", ft_strlen(pipe->argv[0])))
		pipe->exit_code = env_delete(e, NULL);
	else
		pipe->exit_code = exec_others(pipe, envp);
	return (pipe->exit_code);
}

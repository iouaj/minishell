/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:23:18 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/27 13:52:09 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_cmd
{
	char	**argv;
}	t_cmd;

void	exec_cmd(char **argv, char **envp)
{
	char *path;
	int	pid;

	pid = fork();
	if (!pid)
	{
		if (!ft_strncmp(argv[0], "./", 2))
		{
			if (execve(argv[0], argv, envp) == -1)
				printf("%s: no such file or directory\n", argv[0]);
		}
		else
		{
			path = ft_strjoin("/bin/", argv[0]);
			if (execve(path, argv, envp) == -1)
				printf("%s: command not found\n", argv[0]);
			free(path);
		}
		exit(EXIT_SUCCESS);
	}
	else if (pid == -1)
		return ;
	else
		waitpid(pid, NULL, 0);
	return ;
}

void	read_file(int fd, int value)
{
	return ;
}

int	run(t_list *cmds, char **envp)
{
	pid_t		pid;
	int			pipefd[2];
	int			wstatus;
	int			fd;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	printf("%d\n", pid);
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(pipefd[0]);
		fd = dup(1);
		dup2(pipefd[1], 1);
		exec_cmd((*cmds).content, envp);
		dup2(fd, 1);
		close(pipefd[1]);
		close(fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);
		if (cmds != NULL && (*cmds).next != NULL)
		{
			fd = dup(0);
			dup2(pipefd[0], 0);
			run((*cmds).next, envp);
			dup2(fd, 0);
			close(fd);
		}
		else
			read_file(pipefd[0], 1);
		close(pipefd[0]);
		waitpid(-1, &wstatus, 0);
		return (WEXITSTATUS(wstatus));
	}
}


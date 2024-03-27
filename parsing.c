/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:45:27 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/27 17:06:51 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_child(int pipefd[2])
{
	char	buff;

	close(pipefd[1]);
	while (read(pipefd[0], &buff, 1) > 0)
		write(STDOUT_FILENO, &buff, 1);
	write(STDOUT_FILENO, "\n", 1);
	close(pipefd[0]);
}

int	do_pipe(char **splitter)
{
	int		pipefd[2];
	int		pid;

	if (pipe(pipefd) == -1)
		error("pipe");
	pid = fork();
	if (pid == -1)
		error("fork");
	if (!pid) //Child Process
	{
		exec_child(pipefd);
		exit(EXIT_SUCCESS);
	}
	else //Parent Process
	{
		close(pipefd[0]);
		write(pipefd[1], splitter[2], ft_strlen(splitter[2]));
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		return (1);
	}
}

int	check_pipe(char **splitter)
{
	int	i;
	int	j;

	i = 0;
	if (!splitter)
		return (0);
	while (splitter[i])
	{
		j = 0;
		while (splitter[i][j])
		{
			if (splitter[i][j] == '|')
			{
				do_pipe(splitter);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	exec_others(char *argv[], char *envp[])
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
			printf("command worked/n");
			free(path);
		}
		exit(EXIT_SUCCESS);
	}
	else if (pid == -1)
		return (0);
	else
		waitpid(pid, NULL, 0);
	return (1);
}

void	check_env(char **splitter, t_env *e)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (splitter && splitter[i])
	{
		j = 0;
		while (splitter[i][j])
		{
			if (splitter[i][j] == '$')
			{
				temp = ft_strtrim(splitter[i] + j, " $\n\t\b><;");
				free(splitter[i]);
				splitter[i] = ft_strdup(get_env(temp, e));
			}
			j++;
		}
		i++;
	}
}

int	parsing(char *str, t_env **e, char *envp[])
{
	char	**splitter;
	int		value;

	splitter = ft_strtrim_splitter(ft_split(str, ' '));
	if (!splitter)
		return (0);
	check_env(splitter, *e);
	if (!ft_strncmp(splitter[0], "pwd", ft_strlen(splitter[0])))
		value = pwd();
	else if (!ft_strncmp(splitter[0], "cd", ft_strlen(splitter[0])))
		value = cd(splitter[1], *e);
	else if (!ft_strncmp(splitter[0], "echo", ft_strlen(splitter[0])))
		value =echo(splitter);
	else if (!ft_strncmp(splitter[0], "exit", ft_strlen(splitter[0])))
		value = 0;
	else if (!ft_strncmp(splitter[0], "env", ft_strlen(splitter[0])))
		value = env(*e);
	else if (!ft_strncmp(splitter[0], "export", ft_strlen(splitter[0])))
		value = export(e, splitter[1]);
	else if (!ft_strncmp(splitter[0], "unset", ft_strlen(splitter[0])))
		value = env_delete(e, splitter[1]);
	else
		value = exec_others(splitter, envp);
	free_splitter(splitter);
	return (value);
}



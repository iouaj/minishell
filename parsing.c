/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:45:27 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/22 15:51:55 by iouajjou         ###   ########.fr       */
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

void	parsing(char *str)
{
	char **splitter;

	splitter = ft_strtrim_splitter(ft_split(str, ' '));
	if (check_pipe(splitter))
	{
		free_splitter(splitter);
		return ;
	}
	else
		printf("%s: command not found\n", str);
	free_splitter(splitter);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:52:01 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/27 18:16:05 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	get_argc(t_list *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

char **get_argv(t_list *cmd)
{
	char	**argv;
	int		i;
	t_token	*token;

	argv = malloc(sizeof(char *) * (get_argc(cmd) + 1));
	if (argv)
		return (NULL);
	i = 0;
	while (cmd)
	{
		token = (t_token *) cmd->content;
		if (ft_strncmp(token->str, " ", ft_strlen(token->str)))
		{
			argv[i] = token->str;
			i++;
		}
		cmd = cmd->next;
	}
	return (argv);
}

void	child_execve(t_list *cmd, char *envp[])
{
	char	**argv;
	char	*path;

	argv = get_argv(cmd);
	if (!argv)
		exit(0);
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
	free(argv);
	exit(1);
}

int	exec_others(t_list *cmd, char *envp[])
{
	int		pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
		return (0);
	else if (!pid)
		child_execve(cmd, envp);
	else
		waitpid(pid, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}

int	exec(t_list *cmd, t_env **e, char *envp[])
{
	int	value;
	t_token *token;

	token = NULL;
	if (cmd)
		token = (t_token *)(*cmd).content;
	if (!ft_strncmp(token->str, "pwd", ft_strlen(token->str)))
		value = pwd();
	else if (!ft_strncmp(token->str, "cd", ft_strlen(token->str)))
		value = cd(cmd->next, *e);
	else if (!ft_strncmp(token->str, "echo", ft_strlen(token->str)))
		value = echo(cmd->next);
	else if (!ft_strncmp(token->str, "exit", ft_strlen(token->str)))
		value = 0;
	else if (!ft_strncmp(token->str, "env", ft_strlen(token->str)))
		value = env(*e);
	else if (!ft_strncmp(token->str, "export", ft_strlen(token->str)))
		value = export(e, cmd->next);
	else if (!ft_strncmp(token->str, "unset", ft_strlen(token->str)))
		value = env_delete(e, NULL);
	else
		value = exec_others(cmd, envp);
	return (value);
}




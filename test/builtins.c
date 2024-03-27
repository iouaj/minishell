/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:35:47 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/27 18:25:00 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	pwd(void)
{
	char *output;

	output = getcwd(NULL, 0);
	if (!output)
		return (0);
	printf("%s\n", output);
	free(output);
	return (1);
}

int	cd(t_list *cmd, t_env *e)
{
	char *path;
	t_token	*token;

	if (!cmd)
	{
		path = get_env("HOME", e);
	}
	else
		token = (t_token *) cmd->next->content;
		path = token->str;
	if (chdir(path) == -1)
		printf("cd: not a directory : %s\n", path);
	return (1);
}

int	echo(t_list *cmd)
{
	t_token *token;
	int	trigger;

	cmd = cmd->next;
	token = (t_token *) cmd->content;
	trigger = 0;
	if (!ft_strncmp(token->str, "-n", ft_strlen(token->str)))
	{
		if (cmd->next && cmd->next->next)
			cmd = cmd->next->next;
		else
			return (1);
	}
	while (cmd)
	{
		token = (t_token *) cmd->content;
		printf("%s", token->str);
		cmd = cmd->next;
	}
	if (!trigger)
		printf("\n");
	return (1);
}

int	env(t_env *e)
{
	while (e)
	{
		printf("%s=%s\n", e->name, e->content);
		e = e->next;
	}
	return (1);
}

int	export(t_env **e, t_list *cmd)
{
	char	**splitter_arg;
	t_env	*new;
	t_token	*token;

	cmd = cmd->next;
	if (!cmd)
		return (1);
	token = (t_token *)cmd->content;
	splitter_arg = ft_split(token->str, '=');
	if (!splitter_arg)
		return (0);
	if (!splitter_arg[0])
		return (1);
	if (!splitter_arg[1])
		new = env_create_list(splitter_arg[0], "0");
	else
		new = env_create_list(splitter_arg[0], splitter_arg[1]);
	if (!new)
	{
		perror("malloc");
		free_splitter(splitter_arg);
		return (0);
	}
	env_add(e, new);
	free_splitter(splitter_arg);
	return (export(e, cmd->next));
}

void	free_splitter(char **splitter)
{
	int	i;

	i = 0;
	while (splitter[i])
	{
		free(splitter[i]);
		i++;
	}
	free(splitter);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:35:47 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/25 15:46:01 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pwd(void)
{
	char *output;

	output = getcwd(NULL, 0);
	return (output);
}

void	cd(char *path, t_env *env)
{
	if (!path)
	{
		while (env)
		{
			if (!ft_strncmp(env->name, "HOME", ft_strlen(env->name)))
			{
				path = env->content;
				break ;
			}
			env = env->next;
		}
	}
	if (chdir(path) == -1)
		printf("cd: not a directory : %s\n", path);
}

void	echo(char **splitter)
{
	int	i;

	i = 1;
	if (!ft_strncmp(splitter[i], "-n", ft_strlen(splitter[i])))
		i++;
	while (splitter[i])
	{
		printf("%s", splitter[i]);
		i++;
		if (splitter[i])
			printf(" ");
	}
	if (ft_strncmp(splitter[1], "-n", ft_strlen(splitter[1])))
		printf("\n");
}

void	env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
}

void	export(t_env **e, char *arg)
{
	char	**splitter_arg;
	t_env	*new;

	splitter_arg = ft_split(arg, '=');
	if (!splitter_arg || !splitter_arg[0])
		return ;
	if (!splitter_arg[1])
		new = env_create_list(splitter_arg[0], "0");
	else
		new = env_create_list(splitter_arg[0], splitter_arg[1]);
	if (!new)
	{
		perror("malloc");
		free_splitter(splitter_arg);
		exit(EXIT_FAILURE);
	}
	env_add(e, new);
	free_splitter(splitter_arg);
}

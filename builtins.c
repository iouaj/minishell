/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:35:47 by iouajjou          #+#    #+#             */
/*   Updated: 2024/04/01 14:08:03 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

int	pwd(void)
{
	char	*output;

	output = getcwd(NULL, 0);
	if (!output)
		return (error("getcwd"));
	printf("%s\n", output);
	free(output);
	return (EXIT_SUCCESS);
}

int	cd(t_pipeline *pipe, t_env *e)
{
	char	*path;

	if (!pipe->argv[1])
		path = get_env("HOME", e);
	else
		path = pipe->argv[1];
	if (chdir(path) == -1)
		return (error("chdir"));
	return (EXIT_SUCCESS);
}

int	echo(t_pipeline *pipe)
{
	int	i;

	i = 1;
	if (!ft_strncmp(pipe->argv[1], "-n", ft_strlen(pipe->argv[1])))
		i++;
	while (pipe->argv[i])
	{
		printf("%s", pipe->argv[i]);
		i++;
	}
	if (ft_strncmp(pipe->argv[1], "-n", ft_strlen(pipe->argv[1])))
		printf("\n");
	return (EXIT_SUCCESS);
}

int	env(t_env *e)
{
	while (e)
	{
		printf("%s=%s\n", e->name, e->content);
		e = e->next;
	}
	return (EXIT_SUCCESS);
}

int	export(t_env **e, t_pipeline *pipe, int i)
{
	char	**splitter_arg;
	t_env	*new;

	if (!pipe->argv[i])
		return (EXIT_SUCCESS);
	splitter_arg = ft_split(pipe->argv[i], '=');
	if (!splitter_arg)
		return (error("malloc"));
	if (!splitter_arg[0])
		return (EXIT_SUCCESS);
	if (!splitter_arg[1])
		new = env_create_list(splitter_arg[0], "0");
	else
		new = env_create_list(splitter_arg[0], splitter_arg[1]);
	if (!new)
	{
		free_splitter(splitter_arg);
		return (errno);
	}
	env_add(e, new);
	free_splitter(splitter_arg);
	return (export(e, pipe, i + 1));
}

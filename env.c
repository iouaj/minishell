/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:04:17 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/25 14:09:19 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_env_list(void)
{
	t_env	*env;

	env = env_create_list("HOME", getenv("HOME"));
	return (env);
}

t_env	*env_create_list(char *name, char *content)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->name = ft_strdup(name);
	if (!env->name)
	{
		free(env);
		return (NULL);
	}
	if (content)
	{
		env->content = ft_strdup(content);
		if (!env->content)
		{
			free(env->content);
			free(env);
			return (NULL);
		}
	}
	return (env);
}

void	env_add(t_env **lst, t_env *new)
{
	new->next = *lst;
	*lst = new;
}

void	free_env(t_env *env)
{
	t_env *next;

	while (env)
	{
		free(env->content);
		free(env->name);
		next = env->next;
		free(env);
		env = next;
	}
}

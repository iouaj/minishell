/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:04:17 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/27 17:20:57 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_env	*get_env_list(char *envp[])
{
	t_env	*env;
	char	**splitter_envp;
	int	i;

	i = 0;
	env = NULL;
	while (envp && envp[i])
	{
		splitter_envp = ft_split(envp[i], '=');
		if (!splitter_envp)
		{
			free_env(env);
			return (NULL);
		}
		env_add(&env, env_create_list(splitter_envp[0], splitter_envp[1]));
		if (!env)
			return (NULL);
		free_splitter(splitter_envp);
		i++;
	}
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
	env->next = NULL;
	return (env);
}

void	env_add(t_env **lst, t_env *new)
{
	t_env	*temp;

	temp = *lst;
	if (!(*lst))
		*lst = new;
	else
	{
		while ((*lst)->next)
			lst = &(*lst)->next;
		(*lst)->next = new;
		lst = &temp;
	}
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
	env = NULL;
}

int	env_delete(t_env **e, char *name)
{
	t_env	*to_delete;
	t_env	*temp;

	temp = *e;
	if (!ft_strncmp((*e)->name, name, ft_strlen((*e)->name)))
	{
		*e = (*e)->next;
		return (1);
	}
	while (*e)
	{
		if ((*e)->next && !ft_strncmp((*e)->next->name, name, ft_strlen((*e)->name)))
		{
			to_delete = (*e)->next;
			(*e)->next = (*e)->next->next;
			to_delete->next = NULL;
			free_env(to_delete);
			break ;
		}
		*e = (*e)->next;
	}
	*e = temp;
	return (1);
}

char	*get_env(char *name, t_env *e)
{
	while (e)
	{
		if (!ft_strncmp(e->name, name, ft_strlen(e->name)))
			return (e->content);
		e = e->next;
	}
	return (" ");
}

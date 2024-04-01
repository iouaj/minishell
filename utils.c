/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:31:27 by iouajjou          #+#    #+#             */
/*   Updated: 2024/04/01 13:02:55 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error(char *err)
{
	perror(err);
	return (errno);
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

void	set_error(t_env **e, int value)
{
	while (*e)
	{
		if (!ft_strncmp((*e)->name, "?", ft_strlen((*e)->name)))
		{
			(*e)->content = ft_itoa(value);
			if (!(*e)->content)
				exit(EXIT_FAILURE);
			return ;
		}
		(*e) = (*e)->next;
	}
}

void	free_pipeline(void *content)
{
	t_pipeline	*pipeline;

	pipeline = (t_pipeline *) content;
	free(pipeline->eof);
	free(pipeline);
}

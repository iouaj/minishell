/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:22:05 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/22 15:50:57 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
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

char	**ft_strtrim_splitter(char **splitter)
{
	char	*trim;
	int	i;

	i = 0;
	while (splitter[i])
	{
		trim = ft_strtrim(splitter[i], " \n\t");
		free(splitter[i]);
		splitter[i] = trim;
		i++;
	}
	return (splitter);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:35:47 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/24 20:46:03 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pwd(void)
{
	char *output;

	output = getcwd(NULL, 0);
	return (output);
}

void	cd(char *path)
{
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

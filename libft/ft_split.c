/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:03:47 by iouajjou          #+#    #+#             */
/*   Updated: 2023/11/06 12:03:47 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	pass;
	int	nb;

	i = 0;
	pass = 1;
	nb = 0;
	while (s[i])
	{
		if (s[i] != c && pass == 1)
		{
			nb++;
			pass = 0;
		}
		if (s[i] == c)
			pass = 1;
		i++;
	}
	return (nb);
}

static int	next_string(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

// static char	*dupli(const char *s, char *dup, char c, int len)
// {
// 	int	i;

// 	dup = malloc(sizeof(char) * len + 1);
// 	if (!dup)
// 		return (NULL);
// 	i = 0;
// 	while (s[i] && s[i] != c)
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[i] = 0;
// 	return (dup);
// }

static void	cleanleaks(char **splitter)
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

static char	**cpy(char **splitter, char const *s, char c, int index)
{
	int	i;
	int	len;

	len = next_string(s, c);
	splitter[index] = malloc(sizeof(char) * len + 1);
	if (!splitter[index])
	{
		cleanleaks(splitter);
		return (NULL);
	}
	i = 0;
	while (s[i] && s[i] != c)
	{
		splitter[index][i] = s[i];
		i++;
	}
	splitter[index][i] = 0;
	return (splitter);
}

char	**ft_split(char const *s, char c)
{
	char	**splitter;
	int		i;
	int		len;

	splitter = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!splitter)
		return (NULL);
	i = 0;
	while (s[0])
	{
		if (s[0] != c)
		{
			len = next_string(s, c);
			splitter = cpy(splitter, s, c, i);
			if (!splitter)
				return (NULL);
			i++;
			s += len;
		}
		else
			s++;
	}
	splitter[i] = NULL;
	return (splitter);
}

/*#include <stdio.h>
int main()
{
	char str[] = "test";
	char **splitter = ft_split(str, 0);

	int i = 0;
	if (!splitter)
	{
		printf("NULL");
		return (0);
	}
	while(splitter[i])
	{
		printf("%s\n", splitter[i]);
		i++;
	}
	printf("%s", splitter[i]);
	i = 0;
	while(splitter[i])
	{
		free(splitter[i]);
		i++;
	}
	free(splitter[i]);
	free(splitter);
}*/

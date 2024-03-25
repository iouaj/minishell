/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:28:21 by iouajjou          #+#    #+#             */
/*   Updated: 2023/11/06 12:28:21 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	is_inset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*cpy(char const *src, char *dest, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*trim;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	while (is_inset(set, s1[i]) && s1[i])
		i++;
	while (is_inset(set, s1[len - 1]) && !(len < i))
		len--;
	if (i >= (int)ft_strlen(s1) || !len || len < i)
	{
		trim = malloc(sizeof(char) * 1);
		trim[0] = 0;
		return (trim);
	}
	trim = malloc(sizeof(char) * (len - i + 1));
	if (!trim)
		return (NULL);
	cpy(s1 + i, trim, len - i);
	return (trim);
}

/*#include <stdio.h>

int main()
{
 	char str[] = "*******,,,,///Ceci est un / test**************,,,,";
 	printf("%s", ft_strtrim(str, "*,/"));
}*/

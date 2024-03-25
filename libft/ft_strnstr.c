/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:27:02 by iouajjou          #+#    #+#             */
/*   Updated: 2023/11/06 12:27:02 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	int		end;

	i = 0;
	end = 0;
	if (!s2[i])
		return ((char *) s1);
	while (i < len && s1[i])
	{
		j = 0;
		while (s1[i + j] == s2[j] && (i + j) < len)
		{
			j++;
			if (!s2[j])
				end = 1;
		}
		if (end == 1)
			return ((char *) s1 + i);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>

// int main()
// {
//     char s1[] = "Salut je suis une string";
//     char s2[] = "re";

//     printf("%s", ft_strnstr(s1, s2, 20));
// }

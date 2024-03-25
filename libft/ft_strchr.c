/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:05:52 by iouajjou          #+#    #+#             */
/*   Updated: 2023/11/06 12:05:52 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (c > 255)
		c -= 256;
	while (s[i] != c && s[i])
		i++;
	if (!s[i] && c)
		return (NULL);
	return ((char *) s + i);
}

// #include <stdio.h>

// int main()
// {
//     char str[] = "Coucou";

//     printf("%s", ft_strchr(str, 'u'));
// }

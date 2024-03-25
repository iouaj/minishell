/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:08:45 by iouajjou          #+#    #+#             */
/*   Updated: 2023/11/06 17:08:45 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (c > 255)
		c -= 256;
	if (!s)
		return (NULL);
	while (((unsigned char *)s)[i] != (unsigned char)c && i < n)
		i++;
	if (i == n)
		return (NULL);
	return (((unsigned char *)s) + i);
}

/*#include <stdio.h>

int main()
{
    char str[] = {0, 1, 2, 3, 4, 5};
    printf("%p\n", str);
    printf("%p", ft_memchr(str, 2 + 256, 3));
}*/

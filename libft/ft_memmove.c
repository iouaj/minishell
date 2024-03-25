/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:07:13 by iouajjou          #+#    #+#             */
/*   Updated: 2023/11/06 17:07:13 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;

	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *) src)[i];
			i++;
		}
		return (dest);
	}
	while (i < n)
	{
		((unsigned char *)dest)[n - i - 1] = ((unsigned char *)src)[n - i - 1];
		i++;
	}
	return (dest);
}

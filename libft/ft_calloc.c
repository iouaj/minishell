/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:33:06 by iouajjou          #+#    #+#             */
/*   Updated: 2023/11/06 12:33:06 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	if (nmemb)
	{
		if (!(nmemb * size / nmemb == size))
			return (NULL);
	}
	array = malloc(size * nmemb);
	if (!array)
		return (NULL);
	ft_bzero(array, nmemb * size);
	return (array);
}

/*void *ft_calloc(size_t count, size_t size)
{
    void *res;

    if (size > sizeof(char) * 2147483424 || count > sizeof(char) * 2147483424)
        return (NULL);
    res = malloc(size * count);
    if (!res)
        return (0);
    ft_bzero(res, size * count);
    return (res);
}*/

/*#include <stdio.h>
int main()
{
    ft_calloc(-5, -5);
    if (malloc(0 * -5) == NULL)
        printf("NULL NAZE");
    else
        printf("c'est pas null");
    //printf("%u", test(ft_calloc, SIZE_MAX, SIZE_MAX));
}*/

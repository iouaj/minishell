/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:27:34 by iouajjou          #+#    #+#             */
/*   Updated: 2023/11/06 12:27:34 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (!i && c)
		return (NULL);
	while (i >= 0)
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>

int main()
{
    char str[] = "bonjour";

    printf("%p\n", strrchr(str, 's'));
    printf("%p\n", ft_strrchr(str, 's'));
}*/

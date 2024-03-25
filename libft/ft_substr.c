/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:30:13 by iouajjou          #+#    #+#             */
/*   Updated: 2023/11/06 12:30:13 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	len_s;

	if (start > ft_strlen(s))
	{
		substr = malloc(sizeof(char) * 1);
		substr[0] = 0;
		return (substr);
	}
	len_s = ft_strlen(s + start);
	if (len_s < len)
		len = len_s;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (substr);
	i = 0;
	while (s[start + i] && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = 0;
	return (substr);
}

// #include <stdio.h>

// int main()
// {
// 	char *str = "";
// 	char *sub = ft_substr(str, 6, 10);

// 	printf("%s", sub);
// 	free(sub);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:36:07 by iouajjou          #+#    #+#             */
/*   Updated: 2023/11/06 12:36:07 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nblen(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		if (n == -2147483648)
		{
			n = 214748364;
			i++;
		}
		else
			n = -n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*nb;
	long	nbr;
	int		i;

	nbr = (long) n;
	i = nblen(nbr);
	nb = malloc(sizeof(char) * (i + 1));
	if (!nb)
		return (NULL);
	nb[i] = 0;
	i--;
	if (nbr < 0)
	{
		nb[0] = '-';
		nbr *= -1;
	}
	if (nbr == 0)
		nb[i] = '0';
	while (nbr > 0)
	{
		nb[i] = (nbr % 10) + 48;
		nbr = nbr / 10;
		i--;
	}
	return (nb);
}

// #include <stdio.h>

// int main()
// {
// 	printf("%s", ft_itoa(-2147483647));
// }

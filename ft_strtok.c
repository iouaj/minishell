/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:59:19 by souaguen          #+#    #+#             */
/*   Updated: 2024/04/17 14:32:13 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	*extract_qtoken(char **ptr, char *str, int len)
{
	char	*tmp;
	char	*tmp_q;
	int		i;

	i = len;
	if (ptr == NULL)
		return (NULL);
	tmp_q = ft_strchr(str + i + 1, *(str + i));
	if (i != 0)
	{
		tmp = ft_substr(str, 0, i);
		*ptr = (str + i);
		return (tmp);
	}
	tmp = ft_substr((str + i), 0, (tmp_q - (str + i)) + 1);
	*ptr = (tmp_q + 1);
	return (tmp);
}

char	*extract_token(char **ptr, char *str, int len)
{
	char	*tmp;
	int		i;

	i = len;
	if (i == 0)
	{
		*ptr = (str + 1);
		return (ft_substr(str, 0, 1));
	}
	tmp = ft_substr(str, 0, i);
	*ptr = (str + i);
	return (tmp);
}

char	*ft_strtok(char **ptr, char *delim)
{
	char	*str;
	int		i;

	if (ptr == NULL || *ptr == NULL)
		return (NULL);
	i = 0;
	str = *ptr;
	while (*(str + i) != '\0')
	{
		if (ft_strchr(delim, *(str + i)))
			return (extract_token(ptr, str, i));
		else if ((*(str + i) == '\'' || *(str + i) == '\"')
			&& ft_strchr(str + i + 1, *(str + i)))
			return (extract_qtoken(ptr, str, i));
		i++;
	}
	if (*(str + i) == '\0' && ft_strlen(str) > 0)
	{
		*ptr = NULL;
		return (ft_strdup(str));
	}
	return (NULL);
}

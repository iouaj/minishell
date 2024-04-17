/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:05:38 by souaguen          #+#    #+#             */
/*   Updated: 2024/04/17 15:45:22 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_file(int fd, int fd_out)
{
	char	buf;

	while (read(fd, &buf, 1) > 0)
		ft_putchar_fd(buf, fd_out);
}

char	*ft_skip_whitespace(t_list *lst)
{
	t_token	*token;
	t_list	*cursor;

	cursor = lst;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if (ft_strncmp((*token).str, " ", 2))
			break ;
		cursor = (*cursor).next;
	}
	if (cursor == NULL)
		return (NULL);
	token = (*cursor).content;
	return ((*token).str);
}

char	*get_io_file(t_list *lst, int io, int *a_mode, char **eof)
{
	t_token		*token;
	t_list		*cursor;
	char		*tmp;

	cursor = lst;
	tmp = "<";
	if (io)
		tmp = ">";
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if (ft_strncmp((*token).str, tmp, 2) == 0 && (*token).quoted == 0)
		{
			token = (*(*cursor).next).content;
			if (ft_strncmp((*token).str, tmp, 2) == 0 && (*token).quoted == 0)
			{
				cursor = (*cursor).next;
				if (*tmp == '>')
					*a_mode = 1;
				else if (*tmp == '<')
				{
					*eof = ft_skip_whitespace((*cursor).next);
					return (*eof);
				}
			}
			return (ft_skip_whitespace((*cursor).next));
		}
		cursor = (*cursor).next;
	}
	return (NULL);
}

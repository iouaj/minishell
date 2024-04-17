/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:07:16 by souaguen          #+#    #+#             */
/*   Updated: 2024/04/17 13:05:08 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_pipeline_init(t_list *parsed)
{
	t_pipeline	*pipln;
	t_list		*pipeline;
	t_list		*new;
	// char		*infile;
	// char		*outfile;

	new = NULL;
	pipeline = NULL;
	while (parsed != NULL)
	{
		new = get_next_pipe(&parsed);
		pipln = malloc(sizeof(t_pipeline));
		if (pipln == NULL)
			return (NULL);
		(*pipln).eof = NULL;
		(*pipln).a_mode = 0;
		(*pipln).file_out = get_io_file(new, 1, &(*pipln).a_mode, &(*pipln).eof);
		(*pipln).file_in = get_io_file(new, 0, &(*pipln).a_mode, &(*pipln).eof);
		(*pipln).argv = lst_to_argv(new);
		(*pipln).fd_in = 0;
		(*pipln).fd_out = 1;
		/*if (outfile != NULL)
		{
			if ((*pipln).a_mode)
				(*pipln).fd_out = open((*pipln).file_out, O_RDWR | O_CREAT | O_APPEND, 0644);
			else
				(*pipln).fd_out = open((*pipln).file_out, O_RDWR | O_CREAT, 0644);
		}
		if (infile != NULL && (*pipln).eof == NULL)
			(*pipln).fd_in = open((*pipln).file_in, O_RDONLY);
		*/
		(*pipln).eof = NULL;
		(*pipln).exit_code = 0;
		ft_lstadd_back(&pipeline, ft_lstnew(pipln));
	}
	return (pipeline);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:14:05 by souaguen          #+#    #+#             */
/*   Updated: 2024/03/27 17:36:45 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "mini.h"
// typedef struct s_token
// {
// 	char	*str;
// 	int		quoted;
// }	t_token;

t_list	*parsing_init(char *cmd);
char	*ft_strtok(char **ptr, char *delim);
void	*ft_env(void *content);
void	free_quoted(void *ptr);

#endif

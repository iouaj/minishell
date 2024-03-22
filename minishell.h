/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:42:17 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/22 15:54:06 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
void	free_splitter(char **splitter);
char	**ft_strtrim_splitter(char **splitter);
void	parsing(char *str);
void	error(char *err);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:42:17 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/25 14:15:21 by iouajjou         ###   ########.fr       */
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
# include "libft/libft.h"

typedef struct	s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
void	free_splitter(char **splitter);
char	**ft_strtrim_splitter(char **splitter);
char	*ft_strupper(char *str);
int		parsing(char *str, t_env **env);
void	error(char *err);
char	*ft_strjoin(char const *s1, char const *s2);

//env
void	env_add(t_env **lst, t_env *new);
t_env	*env_create_list(char *name, char *content);
t_env	*get_env_list(void);
void	free_env(t_env *env);

//Command
char	*pwd(void);
void	cd(char *path, t_env *env);
void	echo(char **splitter);
void	env(t_env *env);
void	export(t_env **env, char *arg);
#endif

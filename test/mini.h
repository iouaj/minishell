/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:53:16 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/27 17:41:38 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include "../libft/libft.h"

typedef struct s_token
{
	char	*str;
	int		quoted;
}	t_token;

typedef struct	s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

//env
void	env_add(t_env **lst, t_env *new);
t_env	*env_create_list(char *name, char *content);
t_env	*get_env_list(char *envp[]);
void	free_env(t_env *env);
int		env_delete(t_env **env, char *name);
char	*get_env(char *name, t_env *e);

//builtins
int	pwd(void);
int	cd(t_list *cmd, t_env *e);
int	echo(t_list *cmd);
int	env(t_env *e);
int	export(t_env **e, t_list *cmd);

void	free_splitter(char **splitter);
int	exec(t_list *cmd, t_env **e, char *envp[]);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:14:05 by souaguen          #+#    #+#             */
/*   Updated: 2024/04/11 15:21:05 by iouajjou         ###   ########.fr       */
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
# include <errno.h>

# define ERR_G 1
# define ERR_BLT 2
# define ERR_MEM 125
# define ERR_EXEC 126
# define ERR_NF 127

typedef struct s_pipeline
{
	char	**argv;
	char	*eof;
	int		fd_in;
	int		fd_out;
	int		exit_code;
}	t_pipeline;

typedef struct s_token
{
	char	*str;
	int		quoted;
}	t_token;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_sys
{
	t_env				*e;
	struct termios		old_term;
	char				*input;
	int					pipe;
}	t_sys;

//env
void	env_add(t_env **lst, t_env *new);
t_env	*env_create_list(char *name, char *content);
t_env	*get_env_list(char *envp[]);
void	free_env(t_env *env);
int		env_delete(t_env **env, char *name);
char	*get_env(char *name, t_env *e);

//builtins
int		pwd(void);
int		cd(t_pipeline *pipe, t_env *e);
int		echo(t_pipeline *pipe);
int		env(t_env *e);
int		export(t_env **e, t_pipeline *pipe, int i);

void	free_splitter(char **splitter);
int		exec(t_list *cmd, t_env **e, char *envp[]);

void	set_error(t_env **e, int value);
void	free_pipeline(void *content);
int		error(char *err, int exit_code);

t_list	*parsing_init(char *cmd);
char	*ft_strtok(char **ptr, char *delim);
void	*ft_env(void *content);
void	free_quoted(void *ptr);

int	run(t_list *cmds, t_env **e, char *envp[], t_sys *sys);

void	end_shell(char *str, t_env *e, struct termios old_term);
#endif

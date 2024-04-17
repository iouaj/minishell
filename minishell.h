/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:14:05 by souaguen          #+#    #+#             */
/*   Updated: 2024/04/17 14:31:51 by iouajjou         ###   ########.fr       */
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
# include <fcntl.h>

# define ERR_G 1
# define ERR_BLT 2
# define ERR_MEM 125
# define ERR_EXEC 126
# define ERR_NF 127

typedef struct s_pipeline
{
	char	**argv;
	char	*eof;
	char	*file_out;
	char	*file_in;
	int		fd_in;
	int		fd_out;
	int		a_mode;
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
int		exec(t_pipeline *pipe, t_env **e, char *envp[]);

void	set_error(t_env **e, int value);
void	free_pipeline(void *content);
int		error(char *err, int exit_code);

t_list	*parsing_init(char *cmd);
char	*ft_strtok(char **ptr, char *delim);
void	*ft_env(void *content);
void	free_quoted(void *ptr);

int		run(t_list *cmds, t_env **e, char *envp[], t_sys *sys);

void	end_shell(char *str, t_env *e, struct termios old_term);

void	read_file(int fd_to_read, int fd_to_write);
t_list	*ft_pipeline_init(t_list *parsed);
t_list	*get_next_pipe(t_list **lst);
char	*get_io_file(t_list *lst, int io, int *a_mode, char **eof);
char	**lst_to_argv(t_list *lst);
#endif

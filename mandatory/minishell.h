/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:22:53 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/23 01:07:37 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "./ft_libft/libft.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_SQUOTE,
	TOKEN_DQUOTE,
	TOKEN_PIPE,
	TOKEN_EOF,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ENV,
}	t_token_type;

typedef struct s_ms
{
	char		*value;
	int			type;
	int			merg;
	struct s_ms	*next;
}	t_ms;

typedef struct s_redirection
{
	t_token_type			type;
	char					*file;
	struct s_redirection	*next_re;
}	t_redirection;

typedef struct s_command
{
	char				*name;
	char				**args;
	t_redirection		*redirections;
	int					pipe[2];
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_env
{
	char	**vars;
	int		count;
	int		exit_s;
}			t_env;

void		print_token(t_ms *head);
void		print_com(t_command *com, int key);
void		girv(t_ms *head, t_env *env);
void		reset_signals(void);
int			commands(t_ms	*head);
void		ft_free(t_ms	*head);
int			check_sintax(t_ms *head);
t_command	*token_input(char *input, t_env *env);
char		*shorting_code(char *input, t_env *env);
void		link_list(t_ms *ms1, t_ms *ms2);
t_ms		*make_list(char *value, int type, ...);
t_command	*mk_command(t_ms *head, t_command *prev);
void		ft_executing(t_command	*commands, t_env *env);
t_ms		*process_token(int *s, int *e, char *str, t_ms **head);
void		f_norminette(t_ms *head, t_command *command);
t_ms		*cut_word(char *input, int *i);
int			is_whitespace(char c);
int 		setup_redirections(t_redirection *redirs);

/*			env				*/
t_env		*init_env(char **envp);
char		*ft_getenv(t_env *env, const char *key);

/*          builts in functions  */
int			builts_in(t_command *commands, t_env *env);
int			ft_echo(t_command *commands, t_env *env);
int			ft_cd(t_command *commands, t_env *env);
int			ft_pwd(t_env *env);
int			ft_export(t_command *commands, t_env *env);
int			ft_unset(t_command *commands, t_env *env);
int			ft_env(t_command *commands, t_env *env);
int			ft_exit(t_command *cmd);
int			is_valid_key(char *key);
char		**ft_addenv(t_env *env, char *arg, char *key);
void		sort_env(char **env);

char		**ft_setenv(t_env *env, char *key, char *val);

/*			F_LEAKS			*/
void		free_command(t_command *cmd);
void		free_env(t_env *envs);
void		free_redirections(t_redirection *redir);
void		free_vars(char **arr);

/*			SIGNALS			*/
void		crtl_c(int sig);
void		setup_sig(void);
void		reset_signals(void);


#endif
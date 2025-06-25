/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:54:38 by sael-kha          #+#    #+#             */
/*   Updated: 2025/06/25 13:40:39 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

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
	TOKEN_AND,
	TOKEN_OR,
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
	int					is_builtin;
	int					fd_in;
	int					fd_out;
	int					pid;
	char				*name;
	char				**args;
	t_redirection		*redirections;
	int					pipe[2];
	struct s_command	*and;
	struct s_command	*or;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_env
{
	char	**vars;
	int		count;
	int		exit_s;
}			t_env;

/*			debuging		*/
void		print_token(t_ms *head);
void		print_com(t_command *com, int key);

/*			parc_tokens		*/
int			is_builtin(char *cmd);
int			commands(t_ms	*head);
t_command	*mk_command(t_ms *head, t_command *prev);
void		f_norminette(t_ms *head, t_command *command);
void		ft_executing(t_command	*commands, t_env *env);
t_ms		*process_token(int *s, int *e, char *str, t_ms **head);

/*			token			*/
int			is_whitespace(char c);
int			check_sintax(t_ms *head);
void		girv(t_ms *head, t_env *env);
t_ms		*link_and_unlink(t_ms *head);
t_ms		*cut_word(char *input, int *i);
void		link_list(t_ms *ms1, t_ms *ms2);
t_command	*token_input(char *input, t_env *env);
t_ms		*make_list(char *value, int type, ...);
char		*shorting_code(char *input, t_env *env);

/*          builts in functions  */
int			ft_pwd(t_env *env);
void		sort_env(char **env);
void		ft_exit(t_command *cmd, t_env *env);
int			is_valid_key(char *key);
int			ft_cd(t_command *commands, t_env *env);
int			ft_env(t_command *commands, t_env *env);
int			ft_echo(t_command *commands, t_env *env);
int			ft_unset(t_command *commands, t_env *env);
int			ft_export(t_command *commands, t_env *env);
char		**ft_addenv(t_env *env, char *arg, char *key);
char		**ft_setenv(t_env *env, char *key, char *val);
void		builts_in(t_command *commands, t_env *env, int key);

/*			env				*/
t_env		*init_env(char **envp);
char		*ft_getenv(t_env *env, const char *key);

/*			signals			*/
void		crtl_c(int sig);
void		setup_sig(void);
void		reset_signals(void);

/*			f_leaks			*/
void		free_env(t_env *envs);
void		free_vars(char **arr);
void		ft_free(t_ms	*head);
void		ft_free_token(t_ms *token);
void		free_command(t_command *cmd);
void		free_redirections(t_redirection *redir);

/*			exec			*/
void		father(t_command *cmd);
void		child(t_command *cmd, t_env *env);
void		and_or(t_command *cmd, t_env *env);
void		ft_wait(int *exit_s, t_command *cmd);
void		ft_exec(t_command *commands, t_env *env);
int			set_red(t_redirection *redirs, int oldfd);
void		khadem_program(t_command *cmd, t_env *env);

#endif
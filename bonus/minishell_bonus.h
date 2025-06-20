/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-kha <sael-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:54:38 by sael-kha          #+#    #+#             */
/*   Updated: 2025/06/17 22:40:13 by sael-kha         ###   ########.fr       */
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
int			commands(t_ms	*head);
t_command	*mk_command(t_ms *head, t_command *prev);
void		f_norminette(t_ms *head, t_command *command);
void		ft_executing(t_command	*commands, t_env *env);
t_ms		*process_token(int *s, int *e, char *str, t_ms **head);

/*			token			*/
int			is_whitespace(char c);
int			check_sintax(t_ms *head);
void		girv(t_ms *head, t_env *env);
t_ms		*cut_word(char *input, int *i);
void		link_list(t_ms *ms1, t_ms *ms2);
t_command	*token_input(char *input, t_env *env);
t_ms		*make_list(char *value, int type, ...);
char		*shorting_code(char *input, t_env *env);


/*			env				*/
t_env		*init_env(char **envp);
char		*ft_getenv(t_env *env, const char *key);

/*			signals			*/
void		crtl_c(int sig);
void		setup_sig(void);
void		reset_signals(void);

/*			f_leaks			*/
void		free_env(t_env *envs);
void		ft_free(t_ms	*head);
void		free_command(t_command *cmd);
void		free_redirections(t_redirection *redir);

#endif
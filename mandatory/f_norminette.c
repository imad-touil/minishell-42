/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_norminette.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-kha <sael-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:29:17 by sael-kha          #+#    #+#             */
/*   Updated: 2025/06/23 19:39:47 by sael-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	f_norminette(t_ms *head, t_command *command)
{
	command->next = NULL;
	if (head && head->type == TOKEN_PIPE)
	{
		if (head->next || head->type != TOKEN_EOF)
			command->next = mk_command(head->next, command);
	}
}

void	free_redirections(t_redirection *redir)
{
	t_redirection	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next_re;
		free(tmp->file);
		free(tmp);
	}
}

void	free_command(t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	free(cmd->name);
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	free_redirections(cmd->redirections);
	free_command(cmd->next);
	free(cmd);
}

void	free_env(t_env *envs)
{
	int	i;

	i = 0;
	while (envs->vars[i])
	{
		free(envs->vars[i]);
		i++;
	}
	free(envs->vars);
	free(envs);
}

void	ft_free_token(t_ms *token)
{
	free(token->value);
	free(token);
}

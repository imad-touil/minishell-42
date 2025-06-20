/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:26:27 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/20 14:26:28 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

int	commands(t_ms *head)
{
	int	i;

	i = 0;
	while (head->type == TOKEN_WORD 
		|| head->type == TOKEN_SQUOTE || head->type == TOKEN_DQUOTE)
	{
		i++;
		head = head->next;
		if (!head || head->type == TOKEN_EOF)
			break ;
	}
	return (i);
}

t_ms	*re_pipe(t_ms *head)
{
	while (head && !(head->type == TOKEN_PIPE))
		head = head->next;
	return (head);
}

t_redirection	*mk_redirection(t_ms *head)
{
	t_redirection	*redirection;

	if (!head || (head->type == TOKEN_PIPE || head->type == TOKEN_EOF))
		return (NULL);
	if (!(head->type >= TOKEN_REDIR_IN && head->type <= TOKEN_HEREDOC))
		return (mk_redirection(head->next));
	redirection = malloc(sizeof(t_redirection));
	redirection->type = head->type;
	redirection->next_re = NULL;
	head = head->next;
	if (!head || head->type == TOKEN_EOF)
		return (free(redirection), NULL);
	redirection->file = ft_strdup(head->value);
	redirection->next_re = mk_redirection(head->next);
	return (redirection);
}

void	parc_args(t_ms *head, t_command *com)
{
	int	i;

	i = 0;
	com->args = malloc(999 * sizeof(char *));
	com->name = ft_strdup(head->value);
	com->args[i++] = ft_strdup(head->value);
	head = head->next;
	while (head)
	{
		while (head && (head->type >= TOKEN_REDIR_IN
				&& head->type <= TOKEN_HEREDOC))
		{
			head = head->next;
			if (head != NULL)
				head = head->next;
		}
		if (head && (head->type >= TOKEN_PIPE && head->type <= TOKEN_EOF))
			break ;
		if (head)
		{
			com->args[i++] = ft_strdup(head->value);
			head = head->next;
		}
	}
	com->args[i] = NULL;
}

t_command	*mk_command(t_ms *head, t_command *prev)
{
	t_command	*command;

	if (!head || head->type == TOKEN_EOF)
		return (NULL);
	command = malloc(sizeof(t_command));
	parc_args(head, command);
	command->prev = prev;
	command->next = NULL;
	command->redirections = NULL;
	while (head->type >= TOKEN_WORD && head->type <= TOKEN_DQUOTE)
	{
		head = head->next;
		if (!head || head->type == TOKEN_EOF)
			break ;
	}
	if (head && (head->type >= TOKEN_REDIR_IN && head->type <= TOKEN_HEREDOC))
	{
		command->redirections = mk_redirection(head);
		head = re_pipe(head);
	}
	f_norminette(head, command);
	return (command);
}

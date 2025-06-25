/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mk_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-kha <sael-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:44:40 by sael-kha          #+#    #+#             */
/*   Updated: 2025/06/24 10:06:08 by sael-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ms	*handle_special_tokens(char *input, int *i)
{
	if (input[*i] == '|')
		return (make_list("|", TOKEN_PIPE, (*i)++));
	else if (input[*i] == '>' && input[*i + 1] == '>')
		return (make_list(">>", TOKEN_APPEND, (*i) += 2));
	else if (input[*i] == '>')
		return (make_list(">", TOKEN_REDIR_OUT, (*i)++));
	else if (input[*i] == '<' && input[*i + 1] == '<')
		return (make_list("<<", TOKEN_HEREDOC, (*i) += 2));
	else if (input[*i] == '<')
		return (make_list("<", TOKEN_REDIR_IN, (*i)++));
	return (NULL);
}

static t_ms	*handle_word_token(char *input, int *i, int start)
{
	char	*word;
	t_ms	*token;

	while (input[*i] && !is_whitespace(input[*i]))
	{
		if (ft_strchr("|<>\"\'", input[*i]))
			break ;
		(*i)++;
	}
	word = ft_substr(input, start, *i - start);
	token = make_list(word, TOKEN_WORD);
	if (!ft_strchr(" \t\n|<>", input[*i]))
		token->merg = 1;
	free(word);
	return (token);
}

static t_ms	*handel_tokens(char *input, int *i)
{
	t_ms	*current;
	int		start;

	while (is_whitespace(input[*i]))
		(*i)++;
	if (!input[*i])
		return (make_list("", TOKEN_EOF));
	start = *i;
	current = handle_special_tokens(input, i);
	if (current)
		return (current);
	if (input[*i] == '\'' || input[*i] == '\"')
		return (cut_word(input, i));
	return (handle_word_token(input, i, start));
}

void	glue_tokens(t_ms *tokens)
{
	t_ms	*current;
	t_ms	*next_node;
	char	*new_str;

	current = tokens;
	while (current != NULL && current->next != NULL)
	{
		if (current->merg == 1)
		{
			next_node = current->next;
			new_str = ft_strjoin(current->value, next_node->value);
			free(current->value);
			current->value = new_str;
			current->next = next_node->next;
			current->merg = next_node->merg;
			free(next_node->value);
			free(next_node);
		}
		else
			current = current->next;
	}
}

t_command	*token_input(char *input, t_env *env)
{
	t_ms		*head;
	t_ms		*current;
	t_command	*com;
	int			i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		current = handel_tokens(input, &i);
		if (!current)
			return (ft_free(head), env->exit_s = 2, NULL);
		if (!head)
			head = current;
		else
			link_list(head, current);
	}
	if (head && !check_sintax(head))
		return (ft_free(head), env->exit_s = 2, NULL);
	girv(head, env);
	glue_tokens(head);
	head = link_and_unlink(head);
	com = mk_command(head, NULL);
	ft_free(head);
	return (com);
}

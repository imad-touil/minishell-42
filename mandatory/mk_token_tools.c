/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mk_token_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-kha <sael-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:41:51 by sael-kha          #+#    #+#             */
/*   Updated: 2025/06/17 18:42:37 by sael-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms	*make_list(char *value, int type, ...)
{
	t_ms	*ms;

	ms = malloc(sizeof(t_ms));
	if (!ms)
	{
		perror("Error : ");
		exit(1);
	}
	ms->value = ft_strdup(value);
	ms->type = type;
	ms->next = NULL;
	ms->merg = 0;
	return (ms);
}

void	link_list(t_ms *ms1, t_ms *ms2)
{
	while (ms1->next)
		ms1 = ms1->next;
	ms1->next = ms2;
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void	girv(t_ms *head, t_env *env)
{
	char	*tmp;

	while (head)
	{
		if (head->type == TOKEN_WORD || head->type == TOKEN_DQUOTE)
		{
			tmp = head->value;
			head->value = shorting_code(head->value, env);
			free(tmp);
		}
		head = head->next;
	}
}

t_ms	*cut_word(char *input, int *i)
{
	char	c;
	char	*word;
	t_ms	*token;
	int		start;

	c = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != c)
		(*i)++;
	if (!input[*i])
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (NULL);
	}
	word = ft_substr(input, start, *i - start);
	if (c == '\'')
		token = make_list(word, TOKEN_SQUOTE);
	else
		token = make_list(word, TOKEN_DQUOTE);
	(*i)++;
	if (!ft_strchr(" \t\n|<>", input[*i]))
		token->merg = 1;
	free(word);
	return (token);
}

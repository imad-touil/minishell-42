/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mk_token_tools_2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-kha <sael-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:38:53 by sael-kha          #+#    #+#             */
/*   Updated: 2025/06/23 19:32:22 by sael-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_ms	*link_and_unlink(t_ms *head)
{
	t_ms	*cur;
	t_ms	*tmp;

	if (!head)
		return (NULL);
	while (head && !ft_strlen(head->value) && head->type == TOKEN_WORD)
	{
		tmp = head;
		head = head->next;
		ft_free_token(tmp);
	}
	cur = head;
	while (cur && cur->next)
	{
		if (!ft_strlen(cur->next->value) && cur->next->type == TOKEN_WORD)
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			ft_free_token(tmp);
		}
		else
			cur = cur->next;
	}
	return (head);
}

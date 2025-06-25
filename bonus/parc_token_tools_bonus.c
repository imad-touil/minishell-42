/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc_token_tools_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-kha <sael-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:40:11 by sael-kha          #+#    #+#             */
/*   Updated: 2025/06/25 11:29:18 by sael-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 99) == 0)
		return (2);
	if (ft_strncmp(cmd, "cd", 99) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 99) == 0)
		return (2);
	if (ft_strncmp(cmd, "export", 99) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 99) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 99) == 0)
		return (2);
	if (ft_strncmp(cmd, "exit", 99) == 0)
		return (1);
	return (0);
}

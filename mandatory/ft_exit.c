/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:32:07 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/21 12:55:56 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(const char *str)
{
	int	i = 0;

	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}


int	ft_exit(t_command *cmd)
{
	int	i;

	i = -1;
	if (!cmd->args[1])
		exit(0);
	if (!is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("exit\nminshell: exit: numeric argument required\n", 2);
		exit(255);
	}
	if (cmd->args[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		exit(1);
	}
	exit(ft_atoi(cmd->args[1]));
}

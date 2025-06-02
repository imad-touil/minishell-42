/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:57:20 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/02 15:26:15 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_command *cmd)
{
	int	i;

	i = -1;
	if (!cmd->args[1])
		exit(0);
	while (cmd->args[1][++i])
	{
		if (!ft_isdigit(cmd->args[1][i]))
		{
			printf("exit\nminshell: exit: %s: numeric argument required\n", cmd->args[1]);
			exit(255); // TODO exit status 
		}
	}
	if (cmd->args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1); // TODO exit status 
	}
	exit(ft_atoi(cmd->args[1]));
}

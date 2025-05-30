/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:53:17 by imatouil          #+#    #+#             */
/*   Updated: 2025/05/30 19:21:30 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_command *commands)
{
	int	i;
	int	key;
	int	newline;

	newline = 0;
	i = 1;
	key = 0;
	while (commands->args[1][++i])
	{
		if (commands->args[1][i] != 'n')
			key = 1;
	}
	if (!ft_strncmp(commands->args[1], "-n", 2) && key)
	{
		newline = 1;
		i = 0;
	}
	else
		i = 1;
	while (commands->args[++i])
	{
		printf("%s", commands->args[i]);
		if (commands->args[i + 1])
			printf(" ");
	}
	if (newline)
		printf("\n");
	exit(0);
}

void	builts_in(t_command *commands)
{
	if (!ft_strncmp(commands->name, "echo", ft_strlen("echo")))
		ft_echo(commands);
	printf("From Here\n");
}
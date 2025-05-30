/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:53:17 by imatouil          #+#    #+#             */
/*   Updated: 2025/05/30 17:15:11 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_command *commands)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	if (commands->args[1] && !ft_strncmp(commands->args[1], "-n", 2))
	{
		newline = 0;
		i++;
	}
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
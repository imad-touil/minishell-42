/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:29:31 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/01 21:29:53 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_command *commands)
{
	int	i;
	int	key;
	int	newline;

	newline = 0;
	key = 0;
	i = 1;
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
	return (0);
}

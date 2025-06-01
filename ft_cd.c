/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:28:16 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/01 21:28:57 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_command *commands)
{
	int	tmp;

	if (!commands->args[1])
	{
		printf("|   %s   |\n", getenv("HOME"));
		tmp = chdir(getenv("HOME"));
		if (tmp)
			perror("cd: ");
	}
	else
	{
		tmp = chdir(commands->args[1]);
		if (tmp)
			perror("cd: ");
	}
	return (0);
}

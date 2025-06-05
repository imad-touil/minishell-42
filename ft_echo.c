/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:28:49 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/05 22:45:53 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid(char *arg)
{
	int	i;

	if (!ft_strncmp(arg, "-n", 2))
	{
		i = 1;
		while (arg[++i])
		{
			if (arg[i] != 'n')
				return (-1);
		} 
	}
	else
		return (-1);
	return (0);
}

static void	print_args(char **args, int	start)
{
	while (args[start])
	{
		printf("%s", args[start]);
		start++;
		if (args[start])
			printf(" ");
	}
}

int	ft_echo(t_command *commands, t_env *env) 
{
	int	i;
	int	state;

	i = 0;
	state = 1;
	while (commands->args[++i])
	{
		if (is_valid(commands->args[i]))
		{
			state = 0;
			break ;
		}
	}
	print_args(commands->args, i);
	if (i == 1)
		printf("\n");
	env->exit_s = 0;
	return (env->exit_s);
}

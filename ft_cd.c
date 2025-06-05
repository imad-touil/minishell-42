/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:29:12 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/05 23:21:26 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handel_error(t_env *env)
{
	env->exit_s = 1;
	perror("cd: ");
	return (0);
}

int	ft_cd(t_command *commands, t_env *env)
{
	int	tmp;

	if (!commands->args[1])
	{
		tmp = chdir(getenv("HOME"));
		if (tmp)
			return (handel_error(env));
	}
	else
	{
		tmp = chdir(commands->args[1]);
		if (tmp)
			return (handel_error(env));
	}
	env->exit_s = 0;
	return (env->exit_s);
}

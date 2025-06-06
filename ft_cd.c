/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:29:12 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/06 01:24:22 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_command *commands, t_env *env)
{
	int	tmp;

	tmp = chdir(commands->args[1]);
	if (tmp)
	{
		env->exit_s = 1;
		if (!commands->args[1])
			printf("bash: cd: No such file or directory\n");
		else
			printf("bash: cd: %s: No such file or directory\n", commands->args[1]);
		return (0);
	}
	env->exit_s = 0;
	return (env->exit_s);
}

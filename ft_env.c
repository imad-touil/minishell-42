/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:31:24 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/06 01:44:25 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_command *commands, t_env *env)
{
	int	i;

	if (commands->args[1])
	{
		printf("env: %s: No such file or directory\n", commands->args[1]);
		env->exit_s = 1;
		return (0);
	}
	i = -1;
	while (env->vars[++i])
		printf("%s\n", env->vars[i]);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:28:16 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/05 23:03:54 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builts_in(t_command *commands, t_env *env)
{
	if (!ft_strncmp(commands->name, "echo", 4))
		return (ft_echo(commands, env));
	else if (!ft_strncmp(commands->name, "cd", 2)) // return value
		return (ft_cd(commands, env));
	else if (!ft_strncmp(commands->name, "pwd", 3)) // TODO return value
		return (ft_pwd());
	else if (!ft_strncmp(commands->name, "export", 6)) // TODO return value
		return (ft_export(commands, env));
	// else if (!ft_strncmp(commands->name, "unset", 5))
	// 	ft_unset(commands);
	else if (!ft_strncmp(commands->name, "env", 3))
		return (ft_env(env->vars));
	else if (!ft_strncmp(commands->name, "exit", 4))
		return (ft_exit(commands));
	return (-1); // Return -1 if no builts in functions 
}

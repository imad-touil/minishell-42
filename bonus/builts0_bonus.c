/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts0_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:28:16 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/25 13:38:59 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	builts_in(t_command *commands, t_env *env, int key)
{
	if (commands->redirections && key
		&& !set_red(commands->redirections, commands->fd_in))
	{
		env->exit_s = 1;
		return ;
	}
	if (!ft_strncmp(commands->name, "echo", 99))
		ft_echo(commands, env);
	else if (!ft_strncmp(commands->name, "cd", 99))
		ft_cd(commands, env);
	else if (!ft_strncmp(commands->name, "pwd", 99))
		ft_pwd(env);
	else if (!ft_strncmp(commands->name, "export", 99))
		ft_export(commands, env);
	else if (!ft_strncmp(commands->name, "unset", 99))
		ft_unset(commands, env);
	else if (!ft_strncmp(commands->name, "env", 99))
		ft_env(commands, env);
	else if (!ft_strncmp(commands->name, "exit", 99))
		ft_exit(commands, env);
	if (commands->redirections && key)
	{
		dup2(commands->fd_in, STDIN_FILENO);
		dup2(commands->fd_out, STDOUT_FILENO);
	}
}

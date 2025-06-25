/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tools_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-kha <sael-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:18:54 by sael-kha          #+#    #+#             */
/*   Updated: 2025/06/23 19:31:25 by sael-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	and_or(t_command *cmd, t_env *env)
{
	while (cmd)
	{
		if (cmd->and && !env->exit_s)
		{
			ft_executing(cmd->and, env);
			break ;
		}
		else if (cmd->or && env->exit_s)
		{
			ft_executing(cmd->or, env);
			break ;
		}
		if (cmd->and)
			cmd = cmd->and;
		else if (cmd->or)
			cmd = cmd->or;
		else
			cmd = cmd->next;
	}
}

void	child(t_command *cmd, t_env *env)
{
	reset_signals();
	if (cmd->next)
	{
		close(cmd->pipe[0]);
		dup2(cmd->pipe[1], STDOUT_FILENO);
		close(cmd->pipe[1]);
	}
	if (cmd->prev)
	{
		close(cmd->prev->pipe[1]);
		dup2(cmd->prev->pipe[0], STDIN_FILENO);
		close(cmd->prev->pipe[0]);
	}
	if (cmd->redirections && !set_red(cmd->redirections, cmd->fd_in))
		exit(EXIT_FAILURE);
	if (cmd->is_builtin)
	{
		builts_in(cmd, env, 0);
		exit(env->exit_s);
	}
	ft_exec(cmd, env);
}

void	father(t_command *cmd)
{
	if (cmd->prev)
		close(cmd->prev->pipe[0]);
	if (cmd->next)
		close(cmd->pipe[1]);
}

void	ft_wait(int *exit_s, t_command *cmd)
{
	int			status;
	pid_t		pid;
	t_command	*current;

	current = cmd;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		while (current && current->pid != pid)
			current = current->next;
		if (!current)
			continue ;
		if (!current->next)
		{
			if (WIFEXITED(status))
				*exit_s = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				*exit_s = 128 + WTERMSIG(status);
		}
		pid = waitpid(-1, &status, 0);
		current = cmd;
	}
}

void	khadem_program(t_command *cmd, t_env *env)
{
	if (cmd->name[0] == '/' || cmd->name[0] == '.')
		if (execve(cmd->name, cmd->args, env->vars) == -1)
			return (perror("minishell"), exit(127));
}

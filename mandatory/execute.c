/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:24:24 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/21 13:22:35 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int setup_redirections(t_redirection *redirs)
{
	int	fd;

	while (redirs)
	{

		if (redirs->type == TOKEN_REDIR_IN)
			fd = open(redirs->file, O_RDONLY);
		else if (redirs->type == TOKEN_REDIR_OUT)
			fd = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redirs->type == TOKEN_APPEND)
			fd = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		// else if (redirs->type == TOKEN_HEREDOC)
		// 	fd = handle_heredoc(redirs->file);
		if (fd == -1)
			return (perror("minishell"), 0);
		if (redirs->type == TOKEN_REDIR_IN || redirs->type == TOKEN_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redirs = redirs->next_re;
	}
	return (1);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while(paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	ft_exec(t_command	*commands,t_env *env)
{
	char	*com_path;
	char	*path;
	char	**paths;
	char	*temp;
	int		i;

	if (commands->name[0] == '/' || commands->name[0] == '.')
		if(execve(commands->name,commands->args,env->vars) == -1)
			return (perror("minishell"));
	path = ft_getenv(env, "PATH");
	paths = ft_split(path,':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		com_path = ft_strjoin(temp, commands->name);
		free(temp);
		if(access(com_path, X_OK) == 0)
		{
			reset_signals();
			free_paths(paths);
			if (execve(com_path,commands->args,env->vars) == -1)
            	return (free(com_path), perror("minishell"));
		}
		free(com_path);
		i++;
	}
	free_paths(paths);
	ft_putstr_fd("minishell: command not found\n", STDERR_FILENO);
}

void	ft_wait(int *exit_s)
{
	int	status;

	wait(&status);
	if (WIFEXITED(status))
		*exit_s = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*exit_s = 128 + WTERMSIG(status);
}

void	ft_executing(t_command *cmd, t_env *env)
{
	int	pid;


	if (!cmd)
		return ;
	if (!builts_in(cmd, env))
		return ;

	if (!cmd)
		return;

	pid = fork();
	if (pid == 0)
	{
		if (cmd->redirections && !setup_redirections(cmd->redirections))
			exit(EXIT_FAILURE);
		ft_exec(cmd, env);
		exit(127);
	}else
		ft_wait(&env->exit_s);
}

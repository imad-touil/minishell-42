/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-kha <sael-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:42:12 by sael-kha          #+#    #+#             */
/*   Updated: 2025/06/23 19:40:37 by sael-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(t_redirection *red)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		line = readline("heredoc << ");
		if (!line || !ft_strncmp(line, red->file, ft_strlen(line)))
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

int	set_red(t_redirection *redirs, int oldfd)
{
	int	fd;

	while (redirs)
	{
		if (redirs->type == TOKEN_HEREDOC)
			dup2(oldfd, STDIN_FILENO);
		if (redirs->type == TOKEN_REDIR_IN)
			fd = open(redirs->file, O_RDONLY);
		else if (redirs->type == TOKEN_REDIR_OUT)
			fd = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redirs->type == TOKEN_APPEND)
			fd = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redirs->type == TOKEN_HEREDOC)
			fd = handle_heredoc(redirs);
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
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	ft_exec(t_command	*commands, t_env *env)
{
	char	*com_path;
	char	*path;
	char	**paths;
	char	*temp;
	int		i;

	khadem_program(commands, env);
	path = ft_getenv(env, "PATH");
	paths = ft_split(path, ':');
	i = -1;
	while (path && paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		com_path = ft_strjoin(temp, commands->name);
		free(temp);
		if (access(com_path, X_OK) == 0)
		{
			free_paths(paths);
			if (execve(com_path, commands->args, env->vars) == -1)
				return (free(com_path), perror("minishell"), exit(126));
		}
		free(com_path);
	}
	return (ft_putstr_fd("minishell: command not found\n", STDERR_FILENO),
		free_paths(paths), exit(127));
}

void	ft_executing(t_command *cmd, t_env *env)
{
	t_command	*current;

	if (!cmd)
		return ;
	if (cmd->is_builtin == 1 && (!cmd->prev && !cmd->next))
		builts_in(cmd, env, 1);
	else
	{
		current = cmd;
		while (current)
		{
			if (current->next)
				pipe(current->pipe);
			current->pid = fork();
			if (current->pid == 0)
				child(current, env);
			else
			{
				father(current);
				current = current->next;
			}
		}
		ft_wait(&env->exit_s, cmd);
	}
}

// yes 'test' | head -n 1000 | wc -l
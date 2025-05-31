/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:53:17 by imatouil          #+#    #+#             */
/*   Updated: 2025/05/31 11:18:00 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_command *commands)
{
	int	i;
	int	key;
	int	newline;

	newline = 0;
	key = 0;
	i = 1;
	while (commands->args[1][++i])
	{
		if (commands->args[1][i] != 'n')
			key = 1;
	}
	if (!ft_strncmp(commands->args[1], "-n", 2) && key)
	{
		newline = 1;
		i = 0;
	}
	else
		i = 1;
	while (commands->args[++i])
	{
		printf("%s", commands->args[i]);
		if (commands->args[i + 1])
			printf(" ");
	}
	if (newline)
		printf("\n");
	exit(0);
}

void	ft_cd(t_command *commands)
{
	int	tmp;

	if (!commands->args[1])
	{
		tmp = chdir(getenv("HOME"));
		if (tmp)
			perror("Error: ");
	}
	else
	{
		tmp = chdir(commands->args[1]);
		if (tmp)
			perror("ffError: ");
	}
	exit(0);
}

void	ft_pwd()
{
	char	*buffer;
	char	*pwd;
	
	buffer = malloc(1024);
	if (!buffer)
	{
		perror("error: ");
		exit(1);
	}
	pwd = getcwd(buffer, 1024);
	if (pwd)
	{
		printf("%s\n", pwd);
	}
	else
		perror("pwd");
	exit(0);
}

void	builts_in(t_command *commands)
{
	if (!ft_strncmp(commands->name, "echo", 4))
		ft_echo(commands);
	else if (!ft_strncmp(commands->name, "cd", 2)) //TODO solve the mistake 
		ft_cd(commands);
	else if (!ft_strncmp(commands->name, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(commands->name, "export", 6))
		ft_export(commands);
	// else if (!ft_strncmp(commands->name, "unset", 5))
	// 	ft_unset(commands);
	// else if (!ft_strncmp(commands->name, "env", 3))
	// 	ft_env(commands);
	// else if (!ft_strncmp(commands->name, "exit", 4))
		// ft_exit(commands);
	printf("From Here\n");
}

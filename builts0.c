/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:53:17 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/02 02:53:10 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **env)
{
	int	i;

	i = -1;
	while (++i)
		printf("%s\n", env[i]); // TODO is it the envirement ;
	return (0);
}

int	ft_exit()
{
	exit(EXIT_SUCCESS);
}

int	builts_in(t_command *commands, char **env)
{
	if (env[0][2] == '\0') // TODO just for flags 
		printf("lol\n");
	if (!ft_strncmp(commands->name, "echo", 4))
		return (ft_echo(commands)); // TODO solve -n -n -n ... && return value
	else if (!ft_strncmp(commands->name, "cd", 2)) //TODO solve the mistake  && return value
		return (ft_cd(commands));
	else if (!ft_strncmp(commands->name, "pwd", 3)) // TODO return value
		return (ft_pwd());
	else if (!ft_strncmp(commands->name, "export", 6)) // TODO return value
		return (ft_export(commands, env));
	// else if (!ft_strncmp(commands->name, "unset", 5))
	// 	ft_unset(commands);
	else if (!ft_strncmp(commands->name, "env", 3))
		ft_env(env);
	else if (!ft_strncmp(commands->name, "exit", 4))
		return (ft_exit());
	return (-1); // Return -1 if no builts in functions 
}
 
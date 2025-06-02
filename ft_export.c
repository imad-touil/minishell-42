/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:30:18 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/02 18:09:08 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_id(char *id)
{
	if (!ft_isdigit(id[0]) || id[0] != '_')
		return (0);
	return (-1);
}

int	ft_export(t_command *commands, t_env **env)
{
	char	**new_env;
	int		i;

	if (!commands->args[1])
	{
		i = -1;
		while (env[++i])
			printf("declare -x %s\n", env[i]);
		return (0);
	}
	if (is_valid_id(commands->args[1]) || commands->args[1][0] == '=')
		return (printf("lol export: not an identifier\n"), 1337); // exit status ??
	
	i = 0;
	while ((*env)[i])
		i++;
	// new_env = malloc((i + 2) * sizeof(char *));
	new_env = malloc((i + 2) * sizeof(char *));
	if (!new_env)
		return (perror("export: "), 1337); // exit status ??
	i = -1;
	while ((*env)[++i])
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = ft_strdup(commands->args[1]);
	new_env[i + 1] = NULL;
	env = new_env;
	printf("%s\n",getenv("saf"));
	return (0);
}
// tartib d ziyada machi da2iman kattzad f lakhar;

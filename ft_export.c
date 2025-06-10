/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:30:18 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/10 20:52:19 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key(char *id)
{
	if (ft_isdigit(id[0]))
		return (1);
	return (0);
}

static char	**ft_addEnv(t_command *commands, t_env *env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env->vars[i])
		i++;
	new_env = malloc((i + 2) * sizeof(char *));
	if (!new_env)
		return (perror("export: "), NULL);
	i = -1;
	while (env->vars[++i])
		new_env[i] = ft_strdup(env->vars[i]);
	new_env[i] = ft_strdup(commands->args[1]);
	new_env[i + 1] = NULL;
	env->vars = new_env;
	return (new_env);
}

int	ft_export(t_command *commands, t_env *env)
{
	int		i;
	char	**new_env;
	char	*key;
	char	*value;
	char	**temp;

	if (!commands->args[1])
	{
		i = -1;
		while (env->vars[++i])
			printf("declare -x %s\n", env->vars[i]);
		return (0);
	}
	temp = ft_split(commands->args[1], '=');
	key = temp[0];
	value = temp[1];
	if (is_valid_key(key) || key[0] == '=')
	{
		env->exit_s = 1;
		return (printf("minshell export: '%s' not an identifier\n",
					commands->args[1]), 0);
	}
	new_env = ft_addEnv(commands, env);
	return (0);
}
// tartib d ziyada machi da2iman kattzad f lakhar;

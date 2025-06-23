/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:31:00 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/22 18:18:46 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_vars(char **arr)
{
	int i = 0;
	if (!arr) return;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static char	**ft_rmenv(t_env *env, int pos)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while (env->vars[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (perror("unset"), NULL);
	i = -1;
	j = -1;
	while (env->vars[++i])
	{
		if (i == pos)
		{
			i++;
			continue ;
		}
		new_env[++j] = ft_strdup(env->vars[i]);
	}
	new_env[j] = NULL;
	i = 0;
	while (env->vars[i])
		free(env->vars[i++]);
	free(env->vars);
	env->vars = new_env;
	return (new_env);
}

int	ft_unset(t_command *commands, t_env *env)
{
	int		i;
	char	**key;
	char	**tmp;

	if (!commands->args[1])
		return (0);
	key = ft_split(commands->args[1], '=');
	i = -1;
	while (env->vars[++i])
	{
		tmp = ft_split(env->vars[i], '=');
		if (!ft_strncmp(tmp[0], key[0], ft_strlen(key[0])) &&
			ft_strlen(tmp[0]) == ft_strlen(key[0]))
		{
			free_vars(tmp);
			env->vars = ft_rmenv(env, i);
			break;
		}
		free_vars(tmp);
	}
	free_vars(key);
	return (0);
}

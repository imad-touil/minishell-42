/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-kha <sael-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:31:00 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/24 18:38:32 by sael-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	j = -1;
	i = 0;
	while (env->vars[i])
	{
		if (i != pos)
			new_env[++j] = ft_strdup(env->vars[i]);
		i++;
	}
	new_env[++j] = NULL;
	free_vars(env->vars);
	env->vars = new_env;
	return (new_env);
}

static void	remove_env_key(t_env *env, char *key)
{
	int		j;
	char	**tmp;

	j = -1;
	while (env->vars[++j])
	{
		tmp = ft_split(env->vars[j], '=');
		if (tmp && tmp[0] && !ft_strncmp(tmp[0], key, ft_strlen(key))
			&& ft_strlen(tmp[0]) == ft_strlen(key))
		{
			free_vars(tmp);
			env->vars = ft_rmenv(env, j);
			break ;
		}
		free_vars(tmp);
	}
}

int	ft_unset(t_command *cmds, t_env *env)
{
	int		i;
	char	*key;

	if (!cmds->args[1])
		return (0);
	i = 0;
	while (cmds->args[++i])
	{
		key = cmds->args[i];
		if (key[0] == '=' || !is_valid_key(key))
		{
			ft_putstr_fd("minishell: not a valid identifier\n", 2);
			env->exit_s = 1;
			continue ;
		}
		remove_env_key(env, key);
	}
	return (0);
}

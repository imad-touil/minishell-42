/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envariements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-kha <sael-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:02:14 by sael-kha          #+#    #+#             */
/*   Updated: 2025/06/23 12:19:38 by sael-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(t_env));
	env->vars = malloc(sizeof(char *) * (i + 1));
	j = 0;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) != 0)
		{
			env->vars[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	env->vars[j] = NULL;
	env->count = j;
	env->exit_s = 0;
	return (env);
}

char	*ft_getenv(t_env *env, const char *key)
{
	int		key_len;
	int		i;

	key_len = ft_strlen(key);
	i = 0;
	while (env->vars[i])
	{
		if (ft_strncmp(env->vars[i], key, key_len) == 0
			&& env->vars[i][key_len] == '=')
			return (env->vars[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

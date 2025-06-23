/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envariements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:25:30 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/22 20:08:46 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

t_env    *init_env(char **envp)
{
    t_env    *env;
    int        i;
    int        j;

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

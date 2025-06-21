/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:25:38 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/20 18:03:00 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_setenv(t_env *env, char *key, char *val)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env->vars[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (perror("ft_setenv"), NULL);
	i = -1;
	while (env->vars[++i])
		new_env[i] = ft_strdup(env->vars[i]);
	new_env[i] = ft_strdup(key);
	new_env[i] = ft_strjoin(new_env[i], "=");
	new_env[i] = ft_strjoin(new_env[i], val);
	new_env[i + 1] = NULL;
	env->vars = new_env;
	return (env->vars);
}

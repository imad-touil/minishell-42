/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:25:38 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/23 01:09:54 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_vars(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[i]) + ft_strlen(env[j])) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}



char	**ft_setenv(t_env *env, char *key, char *val)
{
	char	**new_env;
	char	*tmp;
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
	tmp = ft_strjoin(key, "=");
	new_env[i] = ft_strjoin(tmp, val);
	free(tmp);
	new_env[i + 1] = NULL;
	free_vars(env->vars);
	return (env->vars = new_env, env->vars);
}

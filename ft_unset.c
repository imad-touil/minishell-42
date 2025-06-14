/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:31:00 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/14 21:39:21 by imatouil         ###   ########.fr       */
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
	printf("I ==>> %d, Pos ==>> %d\n", i, pos);
	i = 0;
	j = 0;
	while (env->vars[i])
	{
		if (i == pos)
		{
			i++;
			continue ;
		}
		new_env[j] = ft_strdup(env->vars[i]);
		i++;
		j++;
	}
	new_env[j] = NULL;
	env->vars = new_env;
	return (new_env);
}

int	ft_unset(t_command *commands, t_env *env)
{
	int		i;
	char	**key;
	char	**tmp;
	char	**new_env;

	if (!commands->args[1])
		return (0);
	i = -1;
	key = ft_split(commands->args[1], '=');
	while (env->vars[++i])
	{
		tmp = ft_split(env->vars[i], '=');
		if (!ft_strncmp(tmp[0], key[0], ft_strlen(key[0])))
			new_env = ft_rmenv(env, i);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:30:18 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/21 01:49:28 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key(char *key)
{
	if (ft_isdigit(key[0]))
		return (1);
	return (0);
}

static int	is_it_in(t_env *env, char *key)
{
	int	i;

	i = -1;
	while (env->vars[++i])
	{
		if (!ft_strncmp(env->vars[i], key, ft_strlen(key)))
			return (i);
	}
	return (-1);
}

static char	**ft_addenv(t_env *env, char *arg, char *key)
{
	int	i;
	int	pos;

	i = 0;
	pos = is_it_in(env, key);
	if (pos != -1)
		env->vars[pos] = ft_strdup(arg);
	else
		env->vars = ft_setenv(env, key, arg + ft_strlen(key) + 1);
	return (env->vars);
}

static void	ft_zwaq(t_env *env)
{
	int	i;
	int	j;
	
	i = -1;
	while (env->vars[++i])
	{
		printf("declare -x ");
		j = -1;
		while (env->vars[i][++j])
		{
			printf("%c", env->vars[i][j]);
			if (env->vars[i][j] == '=')
				printf("\"");
		}
		printf("\"\n");
	}
}

int	ft_export(t_command *cmds, t_env *env)
{
	int		i;
	char	**tmp;
	char	*key;

	if (!cmds->args[1])
		ft_zwaq(env);
	i = 0;
	while (cmds->args[++i])
	{
		tmp = ft_split(cmds->args[i], '=');
		key = tmp[0];
		if (is_valid_key(key) || cmds->args[i][0] == '=')
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				cmds->args[i]);
			env->exit_s = 1;
		}
		else
			env->vars = ft_addenv(env, cmds->args[i], key);
	}
	// free(tmp);
	return (0);
}

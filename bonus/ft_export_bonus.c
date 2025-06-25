/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-kha <sael-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:30:18 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/23 19:31:42 by sael-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	is_valid_key(char *key)
{
	int	i;

	if (!key || ft_isdigit(key[0]))
		return (0);
	i = -1;
	while (key[++i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
	}
	return (1);
}

static int	is_it_in(t_env *env, char *key)
{
	int		i;
	size_t	len;

	i = -1;
	len = ft_strlen(key);
	while (env->vars[++i])
	{
		if (!ft_strncmp(env->vars[i], key, len)
			&& env->vars[i][len] == '=')
			return (i);
	}
	return (-1);
}

char	**ft_addenv(t_env *env, char *arg, char *key)
{
	int	i;
	int	pos;

	i = 0;
	pos = is_it_in(env, key);
	if (pos != -1)
	{
		free(env->vars[pos]);
		env->vars[pos] = ft_strdup(arg);
	}
	else
		env->vars = ft_setenv(env, key, arg + ft_strlen(key) + 1);
	sort_env(env->vars);
	return (env->vars);
}

static void	ft_zwaq(t_env *env)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	while (env->vars[++i])
	{
		flag = 1;
		printf("declare -x ");
		j = -1;
		while (env->vars[i][++j])
		{
			printf("%c", env->vars[i][j]);
			if (env->vars[i][j] == '=' && flag)
			{
				flag = 0;
				printf("\"");
			}
		}
		if (flag)
			printf("=\"");
		printf("\"\n");
	}
}

int	ft_export(t_command *cmds, t_env *env)
{
	int		i;
	char	**tmp;
	char	*key;

	if (!cmds->args[1])
		return (ft_zwaq(env), 0);
	i = 0;
	while (cmds->args[++i])
	{
		tmp = ft_split(cmds->args[i], '=');
		key = tmp[0];
		if (!tmp || !tmp[0] || cmds->args[i][0] == '=' || !is_valid_key(tmp[0]))
		{
			ft_putstr_fd("minishell: not a valid identifier\n",
				2);
			env->exit_s = 1;
		}
		else
			env->vars = ft_addenv(env, cmds->args[i], key);
		free_vars(tmp);
	}
	return (0);
}

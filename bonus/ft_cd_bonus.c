/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-kha <sael-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:29:12 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/25 11:23:15 by sael-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	ft_addenv1(t_env *env, char *value, char *key)
{
	char	*tmp;
	char	*new_var;
	char	**new_env;
	int		i;

	tmp = ft_strjoin(key, "=");
	new_var = ft_strjoin(tmp, value);
	free(tmp);
	new_env = malloc(sizeof(char *) * (env->count + 2));
	if (!new_env)
		return ;
	i = -1;
	while (env->vars[++i])
		new_env[i] = env->vars[i];
	new_env[i++] = new_var;
	new_env[i] = NULL;
	free(env->vars);
	env->vars = new_env;
	env->count++;
}

static void	update_pwdenv(t_env *env, char *old_pwd, char *new_pwd)
{
	int	i;
	int	oldpwd_flag;

	oldpwd_flag = 0;
	i = -1;
	while (env->vars[++i])
	{
		if (!ft_strncmp(env->vars[i], "PWD=", 4))
		{
			free(env->vars[i]);
			env->vars[i] = ft_strjoin("PWD=", new_pwd);
		}
		else if (!ft_strncmp(env->vars[i], "OLDPWD=", 7))
		{
			free(env->vars[i]);
			env->vars[i] = ft_strjoin("OLDPWD=", old_pwd);
			oldpwd_flag = 1;
		}
	}
	if (!oldpwd_flag)
		ft_addenv1(env, old_pwd, "OLDPWD");
}

int	ft_cd(t_command *commands, t_env *env)
{
	int		ret;
	char	*new_pwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!commands->args[1] || commands->args[1][0] == '\0')
		ret = chdir(ft_getenv(env, "HOME"));
	else
		ret = chdir(commands->args[1]);
	if (ret)
	{
		ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
		return (env->exit_s = 1, 0);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd && old_pwd)
		update_pwdenv(env, old_pwd, new_pwd);
	free(new_pwd);
	free(old_pwd);
	sort_env(env->vars);
	return (env->exit_s = 0, 0);
}

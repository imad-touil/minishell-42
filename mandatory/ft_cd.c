/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:29:12 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/21 01:48:28 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwdenv(t_env *env, char *old_pwd, char *new_pwd)
{
	int	i;

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
		}
	}
}

int	ft_cd(t_command *commands, t_env *env)
{
	int		ret;
	char	*new_pwd;
	char	*old_pwd;

	if (!commands->args[1] || commands->args[1][0] == '\0')
	{
		printf("minishell: cd: path argument required\n");
		return (env->exit_s = 1, 0);
	}
	old_pwd = getcwd(NULL, 0);
	ret = chdir(commands->args[1]);
	if (ret)
	{
		printf("minishell: cd: %s: No such file or directory\n",
			commands->args[1]);
		return (env->exit_s = 1, 0);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd && old_pwd)
		update_pwdenv(env, old_pwd, new_pwd);
	free(new_pwd);
	return (env->exit_s = 0, 0);
}

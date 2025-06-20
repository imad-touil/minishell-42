/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:29:12 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/19 12:48:23 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_command *commands, t_env *env)
{
	int		ret;
	// char	*old_pwd;
	// char	*new_pwd;  after 

	if (!commands->args[1] || commands->args[1][0] == '\0')
	{
		printf("minishell: cd: path argument required\n");
		env->exit_s = 1;
		return (0);
	}
	ret = chdir(commands->args[1]);
	if (ret)
	{
		printf("minishell: cd: %s: No such file or directory\n",
			commands->args[1]);
		env->exit_s = 1;
		return (0);
	}
	env->exit_s = 0;
	return (env->exit_s);
}

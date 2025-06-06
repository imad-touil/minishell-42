/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:29:33 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/06 01:13:38 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env *env)
{
	char	*buffer;
	char	*pwd;
	
	buffer = malloc(1024);
	if (!buffer)
	{
		perror("error: ");
		exit(1);
	}
	pwd = getcwd(buffer, 1024);
	if (pwd)
	{
		printf("%s\n", pwd);
		env->exit_s = 0;
	}
	else
	{
		env->exit_s = 1;
		perror("pwd");
	}
	free(buffer);
	return (0);
}

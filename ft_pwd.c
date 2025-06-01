/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:30:20 by imatouil          #+#    #+#             */
/*   Updated: 2025/06/01 21:30:32 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd()
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
	}
	else
		perror("pwd");
	// exit(0);
}

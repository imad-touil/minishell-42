/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatouil <imatouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:38:03 by sael-kha          #+#    #+#             */
/*   Updated: 2025/06/25 13:49:29 by imatouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

// void	print_token(t_ms *head)
// {
// 	while(head)
// 	{
// 		printf("value: %s\ntype -> %d\nmergeble: %d\n",
// 			head->value, head->type, head->merg);
// 		head = head->next;
// 	}
// }

// void	print_red(t_redirection *red)
// {
// 	printf("\tredirection\t\n");
// 	switch (red->type)
// 	{
// 		case TOKEN_REDIR_IN:    printf("< (input)\n"); break;
// 		case TOKEN_REDIR_OUT:   printf("> (output)\n"); break;
// 		case TOKEN_APPEND:      printf(">> (append)\n"); break;
// 		case TOKEN_HEREDOC:     printf("<< (heredoc)\n"); break;
// 		default:                printf("Unknown (%d)\n", red->type);
// 	}
// 	printf("%s\n",red->file);
// 	if (red->next_re)
// 		print_red(red->next_re);
// }

// void	print_com(t_command *com, int key)
// {
// 	if (!com)
// 		return ;
// 	if (!key)
// 		printf("\tCMD\t\n");
// 	else if(key == 1)
// 		printf("\tAND\t\n");
// 	else
// 		printf("\tor\t\n");
// 	printf("current adress : %p\n", com);
// 	printf("prev adress : %p\n", com->prev);
// 	printf("command %s\n",com->name);
// 	for (int i = 0; com->args[i] != NULL; i++)
// 		printf("args[%d] %s\n", i, com->args[i]);
// 	if(com->redirections)
// 		print_red(com->redirections);
// 	printf("is_builtin : %d\n", com->is_builtin);
// 	printf("fdin : %d\n", com->fd_in);
// 	printf("fdout : %d\n", com->fd_out);
// 	print_com(com->next, 0);
// 	print_com(com->and, 1);
// 	print_com(com->or, 2);
// }

int	main(int ac, char **av, char **env)
{
	t_command	*commands;
	char		*input;
	t_env		*envs;

	(void)av;
	if (ac != 1)
		return (printf("no need for args lady\n"), 1);
	setup_sig();
	envs = init_env(env);
	input = readline("minishell$ ");
	while (input)
	{
		add_history(input);
		commands = token_input(input, envs);
		ft_executing(commands, envs);
		free_command(commands);
		free(input);
		input = readline("minishell$ ");
	}
	printf("exit");
	free_env(envs);
}

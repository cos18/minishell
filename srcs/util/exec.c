/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:41:36 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/08 18:40:37 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_token(void)
{
	int		wc;
	int		pid;
	char	**token_child;

	token_child = token_cpy(NULL);
	pid = fork();
	ft_printf("%d");
	if (pid < 0)
		throw_error(g_bash->token[0], ERRNO_DEFAULT);
	else if (pid == 0)
	{
		char	**env_child = 0;
		execve(token_child[0], token_child, env_child);
		ft_printf("errno: %s\n", strerror(errno));
		exit(0);
	}	
	else
		wc = wait(NULL);
}

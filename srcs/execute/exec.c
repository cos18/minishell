/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:41:36 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/11 18:35:06 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_cmd(t_cmd cmd)
{
	if (cmd.name == NULL)
		return ;
	if (ft_strequ(cmd.name, ""))
		ft_printf("EMPTY CMD\n");
	if (ft_strequ(cmd.name, "echo"))
		ft_printf("ECHO\n");
	else if (ft_strequ(cmd.name, "cd"))
		ft_printf("CD\n");
	else if (ft_strequ(cmd.name, "pwd"))
		ft_printf("PWD\n");
	else if (ft_strequ(cmd.name, "export"))
		ft_printf("EXPORT\n");
	else if (ft_strequ(cmd.name, "unset"))
		ft_printf("UNSET\n");
	else if (ft_strequ(cmd.name, "env"))
		ft_printf("ENV\n");
	else if (ft_strequ(cmd.name, "exit"))
		exit(0);
	else
		ft_printf("EXECVE\n");
}

/*
**void		exec_token(void)
**{
**	int		wc;
**	int		pid;
**	char	**token_child;
**
**	token_child = token_cpy(NULL);
**	pid = fork();
**	ft_printf("%d");
**	if (pid < 0)
**		throw_error(g_bash->token[0], ERRNO_DEFAULT);
**	else if (pid == 0)
**	{
**		char	**env_child = 0;
**		execve(token_child[0], token_child, env_child);
**		ft_printf("errno: %s\n", strerror(errno));
**		exit(0);
**	}	
**	else
**		wc = wait(NULL);
**}
*/

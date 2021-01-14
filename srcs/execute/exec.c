/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:41:36 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/14 18:36:51 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_cmd(t_cmd cmd)
{
	if (cmd.name == NULL)
		return ;
	if (ft_strequ(cmd.name, "echo"))
		ft_echo(cmd);
	else if (ft_strequ(cmd.name, "cd"))
		ft_cd(cmd);
	else if (ft_strequ(cmd.name, "pwd"))
		ft_pwd();
	else if (ft_strequ(cmd.name, "export"))
		ft_export(cmd, &(g_bash->envlst));
	else if (ft_strequ(cmd.name, "unset"))
		ft_unset(cmd, &(g_bash->envlst));
	else if (ft_strequ(cmd.name, "env"))
		ft_env(g_bash->envlst);
	else if (ft_strequ(cmd.name, "exit"))
		exit(0);
	else
		ft_printf("EXECVE\n");
}

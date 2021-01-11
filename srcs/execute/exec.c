/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:41:36 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/11 19:12:58 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_cmd(t_cmd cmd)
{
	if (cmd.name == NULL)
		return ;
	if (ft_strequ(cmd.name, "echo"))
		ft_printf("ECHO\n");
	else if (ft_strequ(cmd.name, "cd"))
		ft_printf("CD\n");
	else if (ft_strequ(cmd.name, "pwd"))
		ft_pwd();
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

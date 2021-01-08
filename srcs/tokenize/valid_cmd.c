/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:55:16 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/08 18:16:03 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		valid_cmd(char *cmd)
{
	if (cmd == NULL)
		return (FALSE);
	if (ft_strequ(cmd, "echo") || ft_strequ(cmd, "cd") ||
		ft_strequ(cmd, "pwd") || ft_strequ(cmd, "export") ||
		ft_strequ(cmd, "unset") || ft_strequ(cmd, "env") ||
		ft_strequ(cmd, "exit"))
		return (TRUE);
	return (FALSE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:12:37 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/11 17:22:33 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_cmd cmd)
{
	if (cmd.name == NULL || cmd.arg == NULL || ft_sp_size(cmd.arg) == 0)
		return ;
	if (chdir(cmd.arg[0]) == -1)
		ft_printf("bash: cd: %s: %s\n", cmd.arg[0], strerror(errno));
}

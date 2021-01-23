/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:20:20 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/23 14:39:03 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_cmd cmd)
{
	int		i;
	int		nl;

	if (cmd.arg == NULL || cmd.arg[0] == NULL)
	{
		ft_putendl_fd("", STDOUT);
		return ;
	}
	nl = 0;
	while (ft_strequ(cmd.arg[nl], "-n"))
		nl++;
	i = nl - 1;
	while (cmd.arg[++i])
	{
		ft_putstr_fd(cmd.arg[i], 1);
		if (cmd.arg[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (!nl)
		ft_putstr_fd("\n", 1);
}

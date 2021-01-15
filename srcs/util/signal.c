/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:34:02 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/15 23:31:06 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int signo)
{
	if (signo == SIGINT)
	{
		if (g_bash->forked)
		{
			g_bash->exit_status = 130;
			ft_printf("\n");
		}
		else
		{
			ft_printf("\b\b  \b\b");
			ft_printf("\n");
			print_prompt(PS1);
			g_bash->exit_status = 1;
		}
	}
	else if (signo == SIGQUIT)
	{
		ft_printf("\b\b  \b\b");
		g_bash->exit_status = 4;
	}
}

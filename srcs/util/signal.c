/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:34:02 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/23 18:46:16 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int signo)
{
	if (signo == SIGINT)
	{
		if (g_bash->forked)
		{
			errno = 130;
			ft_printf("\n");
		}
		else
		{
			ft_printf("\b\b  \b\b");
			ft_printf("\n");
			print_prompt(PS1);
			errno = 1;
		}
	}
	else if (signo == SIGQUIT)
	{
		ft_printf("\b\b  \b\b");
		errno = 4;
	}
}

void	bind_signal(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
}

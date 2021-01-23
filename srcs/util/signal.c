/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:34:02 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/17 21:20:30 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int signo)
{
	if (signo == SIGINT)
	{
		if (g_bash->forked)
		{
			free(g_bash->exit_status->val);
			g_bash->exit_status->val = ft_strdup("130");
			ft_printf("\n");
		}
		else
		{
			ft_printf("\b\b  \b\b");
			ft_printf("\n");
			print_prompt(PS1);
			free(g_bash->exit_status->val);
			g_bash->exit_status->val = ft_strdup("1");
		}
	}
	else if (signo == SIGQUIT)
	{
		ft_printf("\b\b  \b\b");
		free(g_bash->exit_status->val);
		g_bash->exit_status->val = ft_strdup("4");
	}
}

void	bind_signal(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
}

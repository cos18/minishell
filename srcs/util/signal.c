/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:34:02 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/24 05:41:46 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	g_bash->quote = '\0';
	if (g_bash->input)
	{
		free(g_bash->input);
		g_bash->input = NULL;
	}
	if (g_bash->note)
	{
		free(g_bash->note);
		g_bash->note = NULL;
	}
	if (g_bash->forked)
	{
		ft_printf("\n");
		errno = 130;
	}
	else
	{
		ft_printf("\b\b  \b\b");
		ft_printf("\n");
		print_prompt(PS1);
		errno = 1;
	}
}

void	sigquit_handler(int signo)
{
	if (signo == SIGQUIT)
	{
		ft_printf("\b\b  \b\b");
		errno = 4;
	}
}

void	bind_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp2cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:54:52 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/09 16:32:35 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			sp2cmd(char **sp)
{
	size_t	i;
	size_t	size;

	size = ft_sp_size(sp);
	if (sp == NULL || sp[0] == NULL ||
		(g_bash->cmd.arg = (char **)malloc(sizeof(char *) * size)) == 0)
	{
		g_bash->cmd.name = NULL;
		return ;
	}
	g_bash->cmd.name = ft_strdup(sp[0]);
	i = 0;
	while (sp[++i])
		g_bash->cmd.arg[i - 1] = ft_strdup(sp[i]);
	g_bash->cmd.arg[size - 1] = NULL;
}

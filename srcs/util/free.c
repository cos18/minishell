/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:20:30 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/15 00:59:49 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_end_free(void)
{
	free(g_bash->input);
	g_bash->input = NULL;
	free_cmd(&(g_bash->cmd));
}

void	free_cmd(t_cmd *cmd)
{
	size_t	i;

	if (cmd->name)
	{
		free(cmd->name);
		cmd->name = NULL;
	}
	if (cmd->arg)
	{
		i = -1;
		while (cmd->arg[++i])
		{
			free(cmd->arg[i]);
			cmd->arg[i] = NULL;
		}
		free(cmd->arg);
		cmd->arg = NULL;
	}
	if (cmd->token)
		free_split(cmd->token, MAX_SPLIT);
}

int		free_split(char **sep, int word_locate)
{
	int	locate;

	locate = -1;
	while (++locate < word_locate - 1 && sep[locate])
		free(sep[locate]);
	free(sep);
	return (1);
}

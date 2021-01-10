/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:20:30 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/09 18:36:50 by hyukim           ###   ########.fr       */
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
}

int		free_token(char **sep, int word_locate)
{
	int	locate;

	locate = -1;
	while (++locate < word_locate - 1 && sep[locate])
		free(sep[locate]);
	free(sep);
	return (1);
}

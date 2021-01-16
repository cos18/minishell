/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:20:30 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/16 17:22:35 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_end_free(void)
{
	if (g_bash->input)
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
			free(cmd->arg[i]);
		free(cmd->arg);
		cmd->arg = NULL;
	}
	if (cmd->token)
	{
		free(cmd->token);
		cmd->token = NULL;
	}
}

int		free_split(char **sep, int word_locate)
{
	int	locate;

	if (sep == NULL)
		return (1);
	locate = -1;
	while (++locate < word_locate - 1 && sep[locate])
		free(sep[locate]);
	free(sep);
	return (1);
}

void	free_lst(t_list *lst)
{
	if (lst == NULL)
		return ;
	if (lst->next)
		free_lst(lst->next);
	if (lst->content)
		free(lst->content);
	free(lst);
}

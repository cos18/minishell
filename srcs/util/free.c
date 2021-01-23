/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:20:30 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/24 06:15:57 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_end_free(void)
{
	free_str(&g_bash->input);
	g_bash->input = NULL;
	if (g_bash->cmdlst)
		free_cmdlst(g_bash->cmdlst);
	g_bash->cmdlst = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	size_t	i;

	free_str(&cmd->name);
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
	free(cmd);
	cmd = NULL;
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

void	free_cmdlst(t_cmdlst *lst)
{
	if (lst == NULL)
		return ;
	if (lst->next)
		free_cmdlst(lst->next);
	if (lst->data)
		free_cmd(lst->data);
	free(lst);
}

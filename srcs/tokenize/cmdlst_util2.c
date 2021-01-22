/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:18:14 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/23 00:31:58 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			free_left_vars(t_list *tokenlst)
{
	free_lst(tokenlst);
	free_cmdlst(g_bash->cmdlst);
	g_bash->cmdlst = NULL;
	return (FALSE);
}

int			get_token_kind(char *token)
{
	if (ft_strequ(token, "|"))
		return (TOKEN_PIPE);
	else if (ft_strequ(token, ">"))
		return (TOKEN_REDIR_OUT);
	else if (ft_strequ(token, ">>"))
		return (TOKEN_REDIR_OUT_DUP);
	else if (ft_strequ(token, "<"))
		return (TOKEN_REDIR_IN);
	else if (ft_strequ(token, ";"))
		return (TOKEN_SEMI);
	return (TOKEN_DEFAULT);
}

int			add_arglst_to_cmd(t_cmdlst *cmd_loc, t_list *arglst)
{
	t_list	*target;
	char	**result;
	int		locate;

	if (cmd_loc == NULL || arglst == NULL)
		return (TRUE);
	locate = ft_lstsize(arglst);
	result = (char **)malloc_safe(sizeof(char *) * (locate + 1));
	locate = 0;
	target = arglst;
	while (target)
	{
		result[locate++] = strdup_with_home(
			(char *)(((t_list *)(target->content))->content));
		target = target->next;
	}
	result[locate] = NULL;
	cmd_loc->data->arg = result;
	while (arglst)
	{
		target = arglst;
		arglst = arglst->next;
		free(target);
	}
	return (TRUE);
}

void		connect_redir_cmd(t_cmdlst *cmd_loc, t_cmdlst *redir_start)
{
	if (cmd_loc == NULL)
		cmd_loc = cmdlst_get_last(g_bash->cmdlst);
	if (cmd_loc == NULL)
		g_bash->cmdlst = redir_start;
	else
	{
		cmd_loc->next = redir_start;
		redir_start->prev = cmd_loc;
	}
}

void		set_cmd_token(t_cmd *cmd)
{
	int		locate;

	cmd->token = (char **)malloc(sizeof(char *) * (ft_sp_size(cmd->arg) + 2));
	(cmd->token)[0] = cmd->name;
	if (cmd->arg != NULL)
	{
		locate = -1;
		while ((cmd->arg)[++locate])
			(cmd->token)[locate + 1] = (cmd->arg)[locate];
	}
	else
		locate = 0;
	(cmd->token)[locate + 1] = NULL;
}

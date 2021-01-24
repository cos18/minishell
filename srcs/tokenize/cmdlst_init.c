/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 19:22:32 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/24 06:07:55 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		add_cmd(t_list *tokenlst, t_cmdlst **cmd_loc,
						t_list **arglist)
{
	t_list		*result;
	t_cmd		*cmd;

	if (*cmd_loc)
	{
		result = ft_lstnew(tokenlst);
		if (result == NULL)
			return (FALSE);
		ft_lstadd_back(arglist, result);
		return (TRUE);
	}
	cmd = cmd_init((char *)(tokenlst->content));
	*cmd_loc = cmdlst_add_last(&(g_bash->cmdlst), cmd);
	if (cmd->name == NULL || *cmd_loc == NULL)
	{
		free(cmd);
		return (FALSE);
	}
	return (TRUE);
}

static int		add_redir(t_list **tokenlst, t_cmdlst **redir_start)
{
	t_list		*redir;
	t_cmd		*result;

	redir = *tokenlst;
	result = cmd_init((char *)((*tokenlst)->content));
	*tokenlst = (*tokenlst)->next;
	if (*tokenlst == NULL ||
			get_token_kind((char *)((*tokenlst)->content)) != TOKEN_DEFAULT)
	{
		if (result->name)
			free_str(&result->name);
		free(result);
		if (*tokenlst)
			return (throw_token_error((char *)((*tokenlst)->content)));
		*tokenlst = redir;
		return (throw_token_error("newline"));
	}
	result->arg = (char **)malloc_safe(sizeof(char *) * 2);
	(result->arg)[0] = strdup_with_home((char *)((*tokenlst)->content));
	(result->arg)[1] = NULL;
	cmdlst_add_last(redir_start, result);
	return (TRUE);
}

static int		handle_one_command(t_list *tokenlst, t_list *last)
{
	t_cmdlst	*cmd_loc;
	t_cmdlst	*redir_start;
	t_list		*arglst;
	int			status;

	cmd_loc = NULL;
	redir_start = NULL;
	arglst = NULL;
	status = TRUE;
	while (status && tokenlst != last)
	{
		if (get_token_kind(tokenlst->content) == TOKEN_DEFAULT)
			status = add_cmd(tokenlst, &cmd_loc, &arglst);
		else
			status = add_redir(&tokenlst, &redir_start);
		tokenlst = tokenlst->next;
	}
	status = status ? add_arglst_to_cmd(cmd_loc, arglst) : status;
	if (status && redir_start)
		connect_redir_cmd(cmd_loc, redir_start);
	if (status && cmd_loc)
		set_cmd_token(cmd_loc->data);
	if (!status)
		free_cmdlst(redir_start);
	return (status);
}

static int		handle_next_command(t_list *tokenlst)
{
	t_cmd		*result;

	if (tokenlst->next == NULL &&
			get_token_kind((char *)(tokenlst->content)) == TOKEN_PIPE)
		return (throw_token_error("newline"));
	if (tokenlst->next &&
			(get_token_kind((char *)(tokenlst->next->content)) == TOKEN_PIPE ||
			get_token_kind((char *)(tokenlst->next->content)) == TOKEN_SEMI))
		return (throw_token_error((char *)(tokenlst->next->content)));
	result = cmd_init((char *)(tokenlst->content));
	cmdlst_add_last(&(g_bash->cmdlst), result);
	tokenlst->next = NULL;
	free_lst(tokenlst);
	return (TRUE);
}

int				cmdlst_init(t_list *tokenlst)
{
	t_list		*last;
	t_list		*tmp;

	while (tokenlst)
	{
		last = tokenlst;
		while (last->next != NULL && !ft_strequ(last->next->content, ";")
				&& !ft_strequ(last->next->content, "|"))
			last = last->next;
		if (handle_one_command(tokenlst, last->next) == FALSE)
			return (free_left_vars(tokenlst));
		tmp = last->next;
		last->next = NULL;
		free_lst(tokenlst);
		if (tmp)
		{
			last = tmp->next;
			if (handle_next_command(tmp) == FALSE)
				return (free_left_vars(tmp));
			tmp = last;
		}
		tokenlst = tmp;
	}
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 19:16:23 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/21 22:07:01 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdlst		*cmdlst_new(t_cmd *cmd)
{
	t_cmdlst	*result;

	result = (t_cmdlst *)malloc_safe(sizeof(t_cmdlst));
	result->prev = NULL;
	result->data = cmd;
	result->next = NULL;
	return (result);
}

t_cmdlst		*cmdlst_add_next(t_cmdlst *lst, t_cmd *cmd)
{
	t_cmdlst	*result;

	result = cmdlst_new(cmd);
	result->prev = lst;
	result->next = lst->next;
	lst->next = result;
	return (result);
}

t_cmdlst		*cmdlst_add_prev(t_cmdlst *lst, t_cmd *cmd)
{
	t_cmdlst	*result;

	result = cmdlst_new(cmd);
	result->next = lst;
	result->prev = lst->prev;
	lst->prev = result;
	return (result);
}

t_cmdlst		*cmdlst_add_last(t_cmdlst **lst, t_cmd *cmd)
{
	t_cmdlst	*last;

	if (*lst == NULL)
	{
		*lst = cmdlst_new(cmd);
		return (*lst);
	}
	last = *lst;
	while (last && last->next)
		last = last->next;
	return (cmdlst_add_next(last, cmd));
}

t_cmdlst		*cmdlst_get_last(t_cmdlst *lst)
{
	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	return (cmdlst_get_last(lst->next));
}

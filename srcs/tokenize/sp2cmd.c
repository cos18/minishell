/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp2cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:54:52 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/15 18:03:22 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*str2arg(char *s)
{
	char	*result;

	if (ft_strequ(s, "~"))
		result = ft_strdup(g_bash->home);
	else
		result = ft_strdup(s);
	if (result == NULL)
		throw_error("Malloc failed", ERRNO_DEFAULT, TRUE);
	return (result);
}

void		set_arg(t_list *lst, int size)
{
	int		locate;

	g_bash->cmd.arg = (char **)malloc_safe(sizeof(char *) * size);
	locate = 0;
	while (lst)
	{
		g_bash->cmd.arg[locate] = str2arg((char *)(lst->content));
		g_bash->cmd.token[locate + 1] = g_bash->cmd.arg[locate];
		locate++;
		lst = lst->next;
	}
	g_bash->cmd.arg[locate] = NULL;
	g_bash->cmd.token[locate + 1] = NULL;
}

void		sp2cmd(t_list *lst)
{
	int		size;

	size = ft_lstsize(lst);
	if (size == 0 || lst->content == NULL)
		return ;
	g_bash->cmd.token = (char **)malloc_safe(sizeof(char *) * size + 1);
	g_bash->cmd.name = str2arg((char *)(lst->content));
	g_bash->cmd.token[0] = g_bash->cmd.name;
	if (lst->next == NULL)
	{
		g_bash->cmd.arg = NULL;
		g_bash->cmd.token[1] = NULL;
		return ;
	}
	set_arg(lst->next, size);
}

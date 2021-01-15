/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp2cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:54:52 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/15 17:23:52 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*str2arg(char *s)
{
	char		*result;

	if (ft_strequ(s, "~"))
		result = ft_strdup(g_bash->home);
	else
		result = ft_strdup(s);
	if (result == NULL)
		throw_error("Malloc failed", ERRNO_DEFAULT, TRUE);
	return (result);
}

void			sp2cmd(t_list *lst)
{
	size_t	size;
	t_list	*tmp;
	int		locate;

	size = ft_lstsize(lst);
	if (lst == NULL || lst->content == NULL ||
		(g_bash->cmd.arg = (char **)malloc(sizeof(char *) * size)) == 0)
	{
		g_bash->cmd.name = NULL;
		return ;
	}
	g_bash->cmd.token = (char **)malloc_safe(sizeof(char *) * size + 1);
	g_bash->cmd.name = str2arg((char *)(lst->content));
	g_bash->cmd.token[0] = g_bash->cmd.name;
	tmp = lst->next;
	locate = 0;
	while (tmp)
	{
		g_bash->cmd.arg[locate] = str2arg((char *)(tmp->content));
		g_bash->cmd.token[locate + 1] = g_bash->cmd.arg[locate];
		locate++;
		tmp = tmp->next;
	}
	g_bash->cmd.arg[locate] = NULL;
	g_bash->cmd.token[locate + 1] = NULL;
}

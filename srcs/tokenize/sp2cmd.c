/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp2cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:54:52 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/14 19:26:33 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*str2arg(char *s)
{
	char		*ret;
	t_envlst	*env;

	if (s[0] == '$')
	{
		if (s == NULL || ft_strlen(s) < 2)
			return (ft_strdup(s));
		ret = s + 1;
		if ((env = envlst_get(g_bash->envlst, ret)) == NULL)
			return (NULL);
		if ((ret = ft_strdup(env->val)) == NULL)
			return (NULL);
		return (ret);
	}
	if (ft_strequ(s, "~"))
		return (ft_strdup(g_bash->home));
	return (ft_strdup(s));
}

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
		g_bash->cmd.arg[i - 1] = str2arg(sp[i]);
	g_bash->cmd.arg[size - 1] = NULL;
}

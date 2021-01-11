/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:59:43 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/12 03:01:33 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlst		*envlst_init(char **envp)
{
	t_envlst	*result;

	result = NULL;
	while (*envp)
	{
		envlst_add(&result, *envp);
		envp++;
	}
	return (result);
}

char			*envlst_get_val(t_envlst *lst, char *name)
{
	while (lst)
	{
		if (ft_strequ(lst->name, name))
			return (lst->val);
		lst = lst->next;
	}
	return (NULL);
}

void			envlst_free(t_envlst *lst)
{
	if (lst->next)
		envlst_free(lst->next);
	envlst_free_one(lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 02:47:41 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/13 16:48:47 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_envlst *lst)
{
	while (lst)
	{
		if (lst->val != NULL)
		{
			ft_putstr_fd(lst->name, STDOUT);
			ft_putstr_fd("=", STDOUT);
			ft_putendl_fd(lst->val, STDOUT);
		}
		lst = lst->next;
	}
}

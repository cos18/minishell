/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:11:41 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/12 15:28:38 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_unset(t_cmd cmd, t_envlst **lst)
{
	char	**target;

	target = cmd.arg;
	while (*target)
	{
		envlst_del(lst, *target);
		target++;
	}
}

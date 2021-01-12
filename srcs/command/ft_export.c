/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:28:58 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/12 15:42:24 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_export(t_cmd cmd, t_envlst **lst)
{
	char	**target;

	target = cmd.arg;
	while (*target)
	{
		envlst_append(lst, *target);
		target++;
	}
}

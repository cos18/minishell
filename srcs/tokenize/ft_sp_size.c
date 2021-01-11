/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sp_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:54:52 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/09 16:29:16 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_sp_size(char **sp)
{
	size_t	cnt;

	if (sp == NULL)
		return (0);
	cnt = 0;
	while (sp[cnt])
		cnt++;
	return (cnt);
}

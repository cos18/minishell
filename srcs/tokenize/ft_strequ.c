/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:55:16 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/08 18:50:15 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strequ(char *s1, char *s2)
{
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (FALSE);
	i = -1;
	while (s1[++i] && s2[i])
		if (s1[i] != s2[i])
			return (FALSE);
	return (s1[i] == '\0' && s2[i] == '\0' ? TRUE : FALSE);
}

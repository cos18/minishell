/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:34:08 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/22 16:19:06 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_split(char *in, char *spl[])
{
	int		i;
	int		j;

	if (in == NULL || spl == NULL || ft_strlen(in) == 0
		|| ft_sp_size(spl) == 0)
		return (-1);
	i = -1;
	while (in[++i])
	{
		j = -1;
		while (spl[++j])
			if (ft_strncmp(in + i, spl[j], ft_strlen(spl[j])) == 0)
				return (j);
	}
	return (-1);
}

int			is_cur_sp(char *in, char *spl[])
{
	int		i;

	if (in == NULL || *in == '\0')
		return (-1);
	i = -1;
	while (spl[++i])
		if (ft_strncmp(in, spl[i], ft_strlen(spl[i])) == 0)
			return (i);
	return (-1);
}

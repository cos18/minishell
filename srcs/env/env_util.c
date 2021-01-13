/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:24:15 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/13 20:12:21 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_valid_name(char *name, int is_export)
{
	int	check_num;

	if (!name)
		return (FALSE);
	check_num = TRUE;
	while (*name)
	{
		if (check_num == TRUE && ft_isdigit(*name))
			return (FALSE);
		if (ft_isalnum(*name) == FALSE && *name != '_')
		{
			if (is_export && *name == '+' && *(name + 1) == '\0')
				return (TRUE);
			return (FALSE);
		}
		name++;
		check_num = FALSE;
	}
	return (TRUE);
}

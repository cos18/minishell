/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:31:24 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/22 14:43:37 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*strdup_with_home(char *str)
{
	char	*result;

	if (str == NULL)
		return (NULL);
	result = ft_strdup(ft_strequ(str, "~") ? g_bash->home : str);
	if (result == NULL)
		throw_error("Malloc failed", ERRNO_DEFAULT, TRUE);
	return (result);
}

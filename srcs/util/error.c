/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:55:22 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/08 17:09:45 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		throw_error(char *message, int pnum)
{
	if (pnum == ERRNO_DEFAULT)
		pnum = errno;
	ft_printf("minishell: %s: %s", message, strerror(pnum));
	exit(EXIT_FAILURE);
}

void		*malloc_safe(size_t size)
{
	void	*result;

	result = malloc(size);
	if (result == NULL)
		throw_error("Malloc failed", ERRNO_DEFAULT);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:55:22 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/11 18:44:20 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		throw_error(char *message, int pnum, int is_end)
{
	if (pnum == ERRNO_DEFAULT)
		pnum = errno;
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(message, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(strerror(pnum), STDERR);
	if (is_end)
		exit(EXIT_FAILURE);
}

void		*malloc_safe(size_t size)
{
	void	*result;

	result = malloc(size);
	if (result == NULL)
		throw_error("Malloc failed", ERRNO_DEFAULT, TRUE);
	return (result);
}

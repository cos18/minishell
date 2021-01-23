/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:26:01 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/24 06:09:07 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			throw_exit_error(char *arg)
{
	char			*tmp;

	if ((tmp = ft_strjoin("exit: ", arg)) == NULL)
		throw_error("Malloc failed", ERRNO_DEFAULT, TRUE);
	throw_custom_desc_error(tmp, "numeric argument required", FALSE);
	free_str(&tmp);
	return (255);
}

int					ft_exit(t_cmd cmd)
{
	char			*test;
	int				tmp;
	unsigned char	result;

	ft_putendl_fd("exit", STDOUT);
	if (cmd.arg == NULL)
		return (errno);
	test = *(cmd.arg);
	while (*test)
	{
		if (!ft_isdigit(*test))
			return (throw_exit_error(*(cmd.arg)));
		test++;
	}
	if ((cmd.arg)[1] != NULL)
	{
		errno = 1;
		throw_custom_desc_error("exit", "too many arguments", FALSE);
		return (EXIT_TOO_MANY_ARGS);
	}
	tmp = ft_atoi(*(cmd.arg));
	result = (unsigned char)tmp;
	return (result);
}

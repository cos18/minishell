/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:51:14 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/12 02:41:55 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	dir[MAX_PATH_LEN];

	if (getcwd(dir, MAX_PATH_LEN) == NULL)
		throw_error("pwd", errno, FALSE);
	else
		ft_putendl_fd(dir, STDOUT);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:51:14 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/11 16:11:44 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	dir[MAX_PATH_LEN];

	if (getcwd(dir, MAX_PATH_LEN) == NULL)
		ft_printf("pwd: error retrieving current directory: getcwd: \
cannot access parent directories: Permission denied\n");
	else
		ft_printf("%s\n", dir);
}

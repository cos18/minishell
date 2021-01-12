/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:12:37 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/12 16:53:51 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_cmd cmd)
{
	char	*err_msg;

	if (cmd.arg == NULL || ft_sp_size(cmd.arg) == 0 || cmd.arg[0] == NULL)
		return ;
	if (chdir(cmd.arg[0]) == -1)
	{
		if ((err_msg = ft_strjoin("cd: ", cmd.arg[0])) == NULL)
			return ;
		throw_error(err_msg, errno, FALSE);
		free(err_msg);
	}
	envlst_set_pwd(g_bash->envlst);
}

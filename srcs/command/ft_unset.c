/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:11:41 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/14 20:50:27 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_error_handling(char *name)
{
	char	*tmp;
	char	*err_msg;

	errno = EPERM;
	if ((tmp = ft_strjoin("unset: `", name)) == NULL)
		return ;
	err_msg = ft_strjoin(tmp, "\'");
	free(tmp);
	if (err_msg == NULL)
		return ;
	throw_custom_desc_error(err_msg, "not a valid identifier", FALSE);
	free(err_msg);
}

void		ft_unset(t_cmd cmd, t_envlst **lst, char ***path)
{
	char	**target;

	target = cmd.arg;
	while (*target)
	{
		if (env_valid_name(*target, FALSE) == FALSE)
			unset_error_handling(*target);
		else
			envlst_del(lst, *target);
		if (ft_strequ(*target, ENV_PATH))
			reset_path(path, *lst);
		target++;
	}
}

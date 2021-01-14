/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 20:14:50 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/14 20:43:30 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**path_init(t_envlst *envlst)
{
	t_envlst	*path;
	char		**split;

	path = envlst_get(envlst, ENV_PATH);
	if (path == NULL || path->val == NULL)
		return (NULL);
	if ((split = ft_split(path->val, ':')) == NULL)
		throw_error("Malloc failed", ERRNO_DEFAULT, TRUE);
	return (split);
}

void			reset_path(char ***path, t_envlst *envlst)
{
	free_split(*path, MAX_SPLIT);
	*path = path_init(envlst);
}

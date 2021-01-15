/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 20:14:50 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/14 23:59:44 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				**path_init(t_envlst *envlst)
{
	t_envlst		*path;
	char			**split;
	int				locate;
	char			*tmp;

	path = envlst_get(envlst, ENV_PATH);
	if (path == NULL || path->val == NULL)
		return (NULL);
	if ((split = ft_split(path->val, ':')) == NULL)
		throw_error("Malloc failed", ERRNO_DEFAULT, TRUE);
	locate = 0;
	while (split[locate])
	{
		tmp = split[locate];
		if ((split[locate++] = ft_strjoin(tmp, "/")) == NULL)
			throw_error("Malloc failed", ERRNO_DEFAULT, TRUE);
		free(tmp);
	}
	return (split);
}

void				reset_path(char ***path, t_envlst *envlst)
{
	free_split(*path, MAX_SPLIT);
	*path = path_init(envlst);
}

char				*cmd_get_path_join(char **path, char *name)
{
	char			**target;
	DIR				*dir;
	struct dirent	*dent;

	if (path == NULL)
		return (ft_strjoin("./", name));
	target = path;
	while (*target)
	{
		dir = opendir(*target);
		if (dir)
		{
			while ((dent = readdir(dir)))
			{
				if (ft_strequ(dent->d_name, name))
				{
					closedir(dir);
					return (ft_strjoin(*target, name));
				}
			}
			closedir(dir);
		}
		target++;
	}
	return (NULL);
}

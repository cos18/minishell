/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 20:14:50 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/24 06:03:29 by hyukim           ###   ########.fr       */
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
		free_str(&tmp);
	}
	return (split);
}

void				reset_path(char ***path, t_envlst *envlst)
{
	free_split(*path, MAX_SPLIT);
	*path = path_init(envlst);
}

static int			check_path_name(char *target, char *name)
{
	DIR				*dir;
	struct dirent	*dent;

	dir = opendir(target);
	if (dir)
	{
		while ((dent = readdir(dir)))
		{
			if (ft_strequ(dent->d_name, name))
			{
				closedir(dir);
				return (TRUE);
			}
		}
		closedir(dir);
	}
	return (FALSE);
}

char				*cmd_get_path_join(char **path, char *name)
{
	char			*tmp;
	char			**target;

	tmp = name;
	while (*tmp)
	{
		if (*tmp == '/')
			return (ft_strdup(name));
		tmp++;
	}
	if (path == NULL)
		return (ft_strjoin("./", name));
	target = path;
	while (*target)
	{
		if (check_path_name(*target, name))
			return (ft_strjoin(*target, name));
		target++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:28:58 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/24 06:09:57 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_print_env(t_envlst *lst)
{
	while (lst)
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putstr_fd(lst->name, STDOUT);
		if (lst->val)
		{
			ft_putstr_fd("=\"", STDOUT);
			ft_putstr_fd(lst->val, STDOUT);
			ft_putendl_fd("\"", STDOUT);
		}
		else
			ft_putendl_fd("", STDOUT);
		lst = lst->next;
	}
}

static void	export_error_handling(char *equation)
{
	char	*tmp;
	char	*err_msg;

	errno = EPERM;
	if ((tmp = ft_strjoin("export: `", equation)) == NULL)
		return ;
	err_msg = ft_strjoin(tmp, "\'");
	free_str(&tmp);
	if (err_msg == NULL)
		return ;
	throw_custom_desc_error(err_msg, "not a valid identifier", FALSE);
	free_str(&err_msg);
}

void		ft_export(char **target, t_envlst **lst, char ***path)
{
	char	*name;
	int		locate;

	if (target == NULL || *target == NULL)
		export_print_env(*lst);
	while (target && *target)
	{
		if (check_equation(&locate, *target) == FALSE)
		{
			export_error_handling(*target);
			target++;
			continue;
		}
		name = ft_strndup(*target, locate);
		if (env_valid_name(name, TRUE))
			envlst_append(lst, name, *target, locate);
		else
			export_error_handling(*target);
		if (ft_strequ(name, ENV_PATH) || ft_strequ(name, ENV_PATH_WITHPLUS))
			reset_path(path, *lst);
		free_str(&name);
		target++;
	}
}

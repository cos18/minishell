/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:28:58 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/13 17:50:40 by sunpark          ###   ########.fr       */
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
	free(tmp);
	if (err_msg == NULL)
		return ;
	throw_custom_desc_error(err_msg, "not a valid identifier", FALSE);
	free(err_msg);
}

void		ft_export(t_cmd cmd, t_envlst **lst)
{
	char	**target;
	char	*name;
	int		locate;

	target = cmd.arg;
	if (*target == NULL)
		export_print_env(*lst);
	while (*target)
	{
		if (envlst_check_equation(&locate, *target) == FALSE)
		{
			export_error_handling(*target);
			target++;
			continue;
		}
		name = ft_strndup(*target, locate);
		if (env_valid_name(name))
			envlst_append(lst, name, *target, locate);
		else
			export_error_handling(*target);
		free(name);
		target++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:24:15 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/16 15:13:10 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				env_valid_name(char *name, int is_export)
{
	int			check_num;

	if (!name)
		return (FALSE);
	check_num = TRUE;
	while (*name)
	{
		if (check_num == TRUE && ft_isdigit(*name))
			return (FALSE);
		if (ft_isalnum(*name) == FALSE && *name != '_')
		{
			if (is_export && *name == '+' && *(name + 1) == '\0')
				return (TRUE);
			return (FALSE);
		}
		name++;
		check_num = FALSE;
	}
	return (TRUE);
}

t_envlst		*get_env_in_token(char **check)
{
	t_envlst	*result;
	char		*start;
	char		*name;

	start = ++(*check);
	if (**check == '?')
		return (g_bash->exit_status);
	while (**check)
	{
		if (start == *check && !ft_isalnum(**check) && **check != '_')
		{
			(*check)--;
			return (g_envlst_first_wrong);
		}
		if ((start == *check && ft_isnumber(**check)) ||
				(!ft_isalnum(*(*check + 1)) && *(*check + 1) != '_'))
			break ;
		(*check)++;
	}
	if ((name = ft_strndup(start, *check - start + 1)) == NULL)
		throw_error("Malloc failed", ERRNO_DEFAULT, TRUE);
	result = envlst_get(g_bash->envlst, name);
	free(name);
	return (result);
}

int				check_env_len(char **check)
{
	t_envlst	*find;

	if ((find = get_env_in_token(check)) == g_envlst_first_wrong
			|| find == NULL)
		return (0);
	if (find->val == NULL)
		return (0);
	return (ft_strlen(find->val));
}

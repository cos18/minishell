/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 00:22:36 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/24 06:03:18 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				envlst_cnt(t_envlst *lst)
{
	return (lst ? 1 + envlst_cnt(lst->next) : 0);
}

void			envlst_add(t_envlst **lst, char *equation)
{
	t_envlst	*now;
	int			locate;

	if (check_equation(&locate, equation) == FALSE)
		return ;
	if (*lst == NULL)
	{
		*lst = (t_envlst *)malloc_safe(sizeof(t_envlst));
		now = *lst;
	}
	else
	{
		now = *lst;
		while (now->next)
			now = now->next;
		now->next = (t_envlst *)malloc_safe(sizeof(t_envlst));
		now = now->next;
	}
	now->next = NULL;
	now->name = ft_strndup(equation, locate);
	now->val = ((int)ft_strlen(equation) == locate ?
					NULL : ft_strdup(equation + locate + 1));
	if (now->name == NULL ||
			((int)ft_strlen(equation) != locate && now->val == NULL))
		throw_error("Malloc failed", ERRNO_DEFAULT, TRUE);
}

void			envlst_append(t_envlst **lst, char *name, char *equation, int l)
{
	t_envlst	*target;
	int			is_addition;
	char		*tmp;

	is_addition = FALSE;
	if (name[l - 1] == '+')
	{
		name[l - 1] = '\0';
		is_addition = TRUE;
	}
	target = envlst_get(*lst, name);
	if (target == NULL)
		envlst_add(lst, equation);
	else
	{
		tmp = target->val;
		if (is_addition)
			target->val = ft_strjoin((tmp ? tmp : ""), equation + l + 1);
		else
			target->val = ft_strdup(equation + l + 1);
		if (target->val == NULL)
			throw_error("Malloc failed", ERRNO_DEFAULT, TRUE);
		if (tmp)
			free_str(&tmp);
	}
}

void			envlst_del(t_envlst **lst, char *name)
{
	t_envlst	*prev;
	t_envlst	*target;

	if (ft_strequ((*lst)->name, name))
	{
		target = *lst;
		*lst = target->next;
	}
	else
	{
		prev = *lst;
		while (prev->next && ft_strequ(prev->next->name, name) == FALSE)
			prev = prev->next;
		if (prev->next == NULL)
			return ;
		target = prev->next;
		prev->next = target->next;
	}
	if (target->name)
		free_str(&target->name);
	if (target->val)
		free_str(&target->val);
	free(target);
}

char			**envlst_to_char(t_envlst *lst)
{
	char		**result;
	char		*tmp;
	int			locate;

	result = (char **)malloc_safe(sizeof(char *) * (envlst_cnt(lst) + 1));
	locate = 0;
	while (lst)
	{
		if (lst->val)
		{
			tmp = ft_strjoin(lst->name, "=");
			result[locate] = strjoin_free_a(tmp, lst->val);
			if (result[locate] == NULL && free_split(result, locate))
				return (NULL);
			locate++;
		}
		lst = lst->next;
	}
	result[locate] = NULL;
	return (result);
}

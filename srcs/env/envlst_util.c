/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 00:22:36 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/12 02:46:43 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			envlst_free_one(t_envlst *lst)
{
	if (lst)
	{
		if (lst->name)
			free(lst->name);
		if (lst->val)
			free(lst->val);
		free(lst);
	}
}

static int		check_equation(int *locate, char *equation)
{
	*locate = 0;
	while (equation[*locate] != '=' && equation[*locate] != '\0')
		(*locate)++;
	if (*locate == 0 || equation[*locate] == '\0')
		return (FALSE);
	return (TRUE);
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
	now->val = ft_strndup(equation + locate + 1,
							ft_strlen(equation + locate + 1));
	if (now->name == NULL || now->val == NULL)
		throw_error("Malloc failed", ERRNO_DEFAULT, TRUE);
}

void			envlst_append(t_envlst **lst, char *equation)
{
	t_envlst	*target;
	char		*name;
	int			locate;

	if (check_equation(&locate, equation) == FALSE)
		return ;
	name = ft_strndup(equation, locate);
	target = *lst;
	while (target)
	{
		if (ft_strequ(target->name, name))
			break ;
		target = target->next;
	}
	free(name);
	if (target == NULL)
		envlst_add(lst, equation);
	else
	{
		free(target->val);
		target->val = ft_strndup(equation + locate + 1,
									ft_strlen(equation + locate + 1));
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
		envlst_free_one(target);
		return ;
	}
	prev = *lst;
	while (prev && ft_strequ((*lst)->name, name) == FALSE)
		prev = prev->next;
	if (prev == NULL)
		return ;
	target = prev->next;
	prev->next = target->next;
	envlst_free_one(target);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:59:43 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/24 06:02:23 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlst		*envlst_init(char **envp)
{
	t_envlst	*result;

	result = NULL;
	while (*envp)
	{
		envlst_add(&result, *envp);
		envp++;
	}
	envlst_del(&result, ENV_OLDPWD);
	return (result);
}

t_envlst		*envlst_get(t_envlst *lst, char *name)
{
	while (lst)
	{
		if (ft_strequ(lst->name, name))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void			envlst_free(t_envlst *lst)
{
	if (lst == NULL)
		return ;
	if (lst->next)
		envlst_free(lst->next);
	if (lst->name)
		free_str(&lst->name);
	if (lst->val)
		free_str(&lst->val);
	free(lst);
}

static t_envlst	*envlst_add_name(t_envlst *lst, char *name)
{
	while (lst->next)
		lst = lst->next;
	lst->next = (t_envlst *)malloc_safe(sizeof(t_envlst));
	lst = lst->next;
	lst->name = ft_strdup(name);
	lst->next = NULL;
	return (lst);
}

void			envlst_set_pwd(t_envlst *lst)
{
	t_envlst	*oldpwd;
	t_envlst	*pwd;

	oldpwd = envlst_get(lst, ENV_OLDPWD);
	pwd = envlst_get(lst, ENV_PWD);
	if (pwd)
	{
		if (oldpwd == NULL)
			oldpwd = envlst_add_name(lst, ENV_OLDPWD);
		else
			free_str(&oldpwd->val);
		oldpwd->val = pwd->val;
	}
	else
	{
		if (oldpwd)
		{
			free_str(&oldpwd->val);
			oldpwd->val = ft_strdup("");
		}
		pwd = envlst_add_name(lst, ENV_PWD);
	}
	pwd->val = (char *)malloc_safe(MAX_PATH_LEN);
	if (getcwd(pwd->val, MAX_PATH_LEN) == NULL)
		throw_error("Error while set PWD enviroment variable", errno, FALSE);
}

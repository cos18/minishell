/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:34:08 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/22 22:26:32 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_split(char *in, char *spl[])
{
	int		i;
	int		j;

	if (in == NULL || spl == NULL || ft_strlen(in) == 0
		|| ft_sp_size(spl) == 0)
		return (-1);
	i = -1;
	while (in[++i])
	{
		j = -1;
		while (spl[++j])
			if (ft_strncmp(in + i, spl[j], ft_strlen(spl[j])) == 0)
				return (j);
	}
	return (-1);
}

int			is_cur_sp(char *in, char *spl[])
{
	int		i;

	if (in == NULL || *in == '\0')
		return (-1);
	i = -1;
	while (spl[++i])
		if (ft_strncmp(in, spl[i], ft_strlen(spl[i])) == 0)
			return (i);
	return (-1);
}

void		handle_sp(char **start, char *end, t_list **lst)
{
	int		len;
	t_list	*item;

	if (start == NULL || lst == NULL)
		return ;
	if (*end == ' ')
		return ;
	len = ft_strlen(g_sp[is_cur_sp(end, g_sp)]);
	item = (t_list *)malloc_safe(sizeof(t_list));
	item->content = (char *)ft_strndup(end, len);
	item->next = NULL;
	ft_lstadd_back(lst, item);
	*start = (end + len);
}

void		handle_sp2(char **start, char *end, t_list **lst)
{
	if (**start == ' ' && *end == ' ')
		*start += 1;
	else if (is_cur_sp(*start, g_sp) > 0 && is_cur_sp(end, g_sp) > 0)
		handle_sp(start, end, lst);
}

void		cnt_env_len(char **now, char *end, int *env_len)
{
	while (*now != end)
	{
		if (**now == '$')
			*env_len += check_env_len(now);
		(*now)++;
	}
}

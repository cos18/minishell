/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 00:28:42 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/24 06:17:35 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_strequ(char *s1, char *s2)
{
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (FALSE);
	i = -1;
	while (s1[++i] && s2[i])
		if (s1[i] != s2[i])
			return (FALSE);
	return (s1[i] == '\0' && s2[i] == '\0' ? TRUE : FALSE);
}

size_t		ft_sp_size(char **sp)
{
	size_t	cnt;

	if (sp == NULL)
		return (0);
	cnt = 0;
	while (sp[cnt])
		cnt++;
	return (cnt);
}

int			check_equation(int *locate, char *equation)
{
	*locate = 0;
	while (equation[*locate] != '=' && equation[*locate] != '\0')
		(*locate)++;
	if (*locate == 0)
		return (FALSE);
	return (TRUE);
}

char		*strjoin_free_a(char *a, char *b)
{
	char	*result;

	if (a == NULL)
		return (NULL);
	if (b == NULL)
	{
		result = ft_strdup(a);
		free_str(&a);
		return (result);
	}
	result = ft_strjoin(a, b);
	free_str(&a);
	return (result);
}

int			check_double_quote(char *is, char *input)
{
	int		check_backslash;

	if (*input != '\"')
		return (FALSE);
	check_backslash = 0;
	while (is <= (--input))
	{
		if (*input != '\\')
			break ;
		check_backslash++;
	}
	if (check_backslash % 2)
		return (FALSE);
	return (TRUE);
}

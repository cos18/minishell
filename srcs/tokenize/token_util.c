/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 17:29:51 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/11 18:33:52 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**token_cpy(char **token)
{
	char	**result;
	int		locate;
	int		tmp;

	if (token == NULL)
		token = g_bash->token;
	result = (char **)malloc_safe(ft_strlen((char *)token) + 1);
	locate = -1;
	while (token[++locate])
	{
		result[locate] = (char *)malloc_safe(ft_strlen(token[locate]) + 1);
		tmp = -1;
		while (token[locate][++tmp])
			result[locate][tmp] = token[locate][tmp];
		result[locate][tmp] = '\0';
	}
	result[locate] = 0;
	return (result);
}

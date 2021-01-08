/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:27:44 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/08 17:14:24 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_prompt(int ps)
{
	if (ps == PS1)
		ft_printf("minishell$ ");
	if (ps == PS2)
		ft_printf("> ");
}

static char	*ft_join(char *s1, char *s2)
{
	char	*r;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	r = (char *)malloc_safe(ft_strlen(s1) + ft_strlen(s2) + 2);
	i = -1;
	while (s1[++i])
		r[i] = s1[i];
	if (i > 0)
		r[i++] = '\n';
	j = -1;
	while (s2[++j])
		r[i + j] = s2[j];
	r[i + j] = '\0';
	free(s1);
	s1 = NULL;
	free(s2);
	s2 = NULL;
	return (r);
}

static void	handle_quote(char *quote, char *s)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (*quote == '\0')
				*quote = s[i];
			else if (*quote == s[i])
				*quote = '\0';
		}
		else if (s[i] == '\\')
		{
			if (*quote == '\0' && s[i + 1] == '\0')
				*quote = '\\';
			if (s[i + 1] != '\'')
				i++;
		}
	}
}

static char	*handle_str(char *q, char *p, char *s)
{
	if (s == NULL || q == NULL)
		return (NULL);
	if (p == NULL)
	{
		p = (char *)malloc_safe(1);
		p[0] = '\0';
	}
	handle_quote(q, s);
	return (ft_join(p, s));
}

int			get_command(void)
{
	char	*tmp;
	int		gnl_result;
	char	quote;

	quote = '\0';
	while (TRUE)
	{
		if (quote == '\\')
			quote = '\0';
		if ((gnl_result = get_next_line(0, &tmp)) != GNL_READ || tmp == NULL)
		{
			if (g_bash->cmd)
				free(g_bash->cmd);
			return (gnl_result);
		}
		g_bash->cmd = handle_str(&quote, g_bash->cmd, tmp);
		if (quote == '\0')
			break ;
		print_prompt(PS2);
	}
	if (ft_strncmp(g_bash->cmd, "exit", 5) == 0)
		ft_printf("exit\n");
	return (ft_strncmp(g_bash->cmd, "exit", 5) == 0 ?
			GET_CMD_EXIT : GET_CMD_READ);
}

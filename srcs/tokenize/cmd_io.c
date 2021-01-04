/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:27:44 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/04 20:15:56 by hyukim           ###   ########.fr       */
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

	if (!(r = malloc((s1 ? ft_strlen(s1) : 0) + (s2 ? ft_strlen(s2) : 0) + 2)))
		return (NULL);
	i = -1;
	while (s1 && s1[++i])
		r[i] = s1[i];
	i > 0 ? r[i++] = '\n' : FALSE;
	j = -1;
	while (s2 && s2[++j])
		r[i + j] = s2[j];
	r[i + j] = '\0';
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (r);
}

static char	*ft_strpop(char *str, size_t pop)
{
	if (str == NULL || ft_strlen(str) <= pop)
		return (NULL);
	pop -= 1;
	while (str[++pop])
		str[pop] = str[pop + 1];
	return (str);
}

static int	check_quotes(char *str, char *quote)
{
	int		i;

	if (str == NULL || ft_strlen(str) == 0 || quote == NULL)
		return (FALSE);
	i = -1;
	while (str[++i])
	{
		if (*quote == 0 && (str[i] == '\'' || str[i] == '"'))
		{
			*quote = str[i];
			ft_strpop(str, i);
			i--;
		}
		else if (*quote != '\0' && *quote == str[i])
		{
			*quote = '\0';
			ft_strpop(str, i);
			i--;
		}
	}
	return (*quote == '\0');
}

int			get_command(void)
{
	char	*tmp;
	int		gnl_result;
	char	quote;

	quote = '\0';
	while (TRUE)
	{
		if ((gnl_result = get_next_line(0, &tmp)) != GNL_READ || tmp == NULL)
		{
			if (g_bash->cmd)
				free(g_bash->cmd);
			return (gnl_result);
		}
		g_bash->cmd = ft_join(g_bash->cmd, tmp);
		if (check_quotes(g_bash->cmd, &quote) == TRUE)
			break ;
		print_prompt(PS2);
	}
	if (ft_strncmp(g_bash->cmd, "exit", 5) == 0)
		ft_printf("exit\n");
	return (ft_strncmp(g_bash->cmd, "exit", 5) == 0 ?
			GET_CMD_EXIT : GET_CMD_READ);
}

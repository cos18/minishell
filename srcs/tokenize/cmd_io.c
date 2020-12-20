/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:27:44 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/28 23:31:16 by sunpark          ###   ########.fr       */
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

static char	*cmd_join(char *cmd, char *input)
{
	char	*result;
	int		locate;

	if (!input)
		return (NULL);
	result = (char *)malloc((cmd ? ft_strlen(cmd) : 0) + ft_strlen(input) + 1);
	if (result)
	{
		locate = 0;
		while (cmd && *cmd)
		{
			result[locate++] = *cmd;
			cmd++;
		}
		while (*input)
		{
			if (*input == '\\' && *(input + 1) == *input)
				result[locate++] = *(input++);
			else if (*input != '\\')
				result[locate++] = *input;
			input++;
		}
		result[locate] = '\0';
	}
	return (result);
}

static int	check_backslash(char *tmp)
{
	int		backslash;

	backslash = ft_strlen(tmp) - 1;
	while (tmp[backslash] == '\\')
		backslash--;
	backslash = ft_strlen(tmp) - backslash;
	free(tmp);
	return ((backslash % 2) ? FALSE : TRUE);
}

int			get_command(char **cmd)
{
	char	*tmp;
	char	*join_tmp;
	int		gnl_result;

	while (TRUE)
	{
		gnl_result = get_next_line(0, &tmp);
		if (tmp == NULL || gnl_result != GNL_READ)
		{
			if (*cmd)
				free(*cmd);
			return (gnl_result);
		}
		join_tmp = cmd_join(*cmd, tmp);
		if (*cmd)
			free(*cmd);
		*cmd = join_tmp;
		if (check_backslash(tmp) == FALSE)
			break ;
		print_prompt(PS2);
	}
	if (ft_strncmp(*cmd, "exit", 5) == 0)
		ft_printf("exit\n");
	return (ft_strncmp(*cmd, "exit", 5) == 0 ? GET_CMD_EXIT : GET_CMD_READ);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:05:59 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/05 01:16:02 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		get_source(void)
{
	char		**cmd;
	int			cmd_status;

	cmd = &(g_bash->src.buf);
	cmd_status = get_command(cmd);
	if (cmd_status == GET_CMD_ERROR)
		exit(EXIT_FAILURE);
	if (cmd_status == GET_CMD_EXIT || cmd_status == GET_CMD_EOF)
	{
		if (*cmd)
			free(*cmd);
		if (cmd_status == GET_CMD_EOF)
			printf("exit\n");
		return (SOURCE_EXIT);
	}
	g_bash->token = cmd_split(*cmd);
	return (SOURCE_OK);
}

void			cmd_end_free(void)
{
	free_token(g_bash->token, MAX_TOKEN);
}

int				main(void)
{
	t_bash		bash;
	char		**test;

	while (TRUE)
	{
		bash.src.buf = NULL;
		g_bash = &bash;
		print_prompt(PS1);
		if (get_source() == SOURCE_EXIT)
			break ;
		if (g_bash->src.buf != NULL && ft_strlen(g_bash->src.buf))
		{
			test = g_bash->token;
			while (*test)
				ft_printf("|%s|\n", *(test++));
		}
		cmd_end_free();
	}
}

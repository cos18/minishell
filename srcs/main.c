/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:05:59 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/05 01:21:19 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		get_source(void)
{
	int			cmd_status;

	cmd_status = get_command();
	if (cmd_status == GET_CMD_ERROR)
		exit(EXIT_FAILURE);
	if (cmd_status == GET_CMD_EXIT || cmd_status == GET_CMD_EOF)
	{
		if (g_bash->cmd)
			free(g_bash->cmd);
		if (cmd_status == GET_CMD_EOF)
			printf("exit\n");
		return (SOURCE_EXIT);
	}
	g_bash->token = cmd_split(g_bash->cmd);
	return (SOURCE_OK);
}

int				main(void)
{
	t_bash		bash;
	char		**test;

	while (TRUE)
	{
		bash.cmd = NULL;
		g_bash = &bash;
		print_prompt(PS1);
		if (get_source() == SOURCE_EXIT)
			break ;
		if (g_bash->cmd != NULL && ft_strlen(g_bash->cmd) != 0)
		{
			test = g_bash->token;
			while (*test)
				ft_printf("|%s|\n", *(test++));
		}
		cmd_end_free();
	}
}

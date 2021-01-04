/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:05:59 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/04 20:47:36 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				get_source(void)
{
	char		**cmd;
	int			cmd_status;

	cmd = &(g_bash->cmd);
	cmd_status = get_command();
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
	return (SOURCE_OK);
}

int				main(void)
{
	t_bash		bash;
	char		*cmd;

	cmd = NULL;
	while (TRUE)
	{
		bash.cmd = NULL;
		g_bash = &bash;
		print_prompt(PS1);
		if (get_source() == SOURCE_EXIT)
			break ;
		if (g_bash->cmd != NULL && ft_strlen(g_bash->cmd) != 0)
			ft_printf("%s\n", g_bash->cmd);
		free(cmd);
	}
}

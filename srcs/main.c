/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:05:59 by sunpark           #+#    #+#             */
/*   Updated: 2020/12/20 17:37:12 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				get_source()
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
	return (SOURCE_OK);
}

int				main(void)
{
	t_bash		bash;
	char		*cmd;

	while (TRUE)
	{
		bash.src.buf = NULL;
		g_bash = &bash;
		print_prompt(PS1);
		if (get_source() == SOURCE_EXIT)
			break ;
		src_set();
		if (g_bash->src.buf != NULL && g_bash->src.bufsize != 0)
			ft_printf("%s\n", g_bash->src.buf);
		free(cmd);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:05:59 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/11 18:28:55 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		get_source(void)
{
	int			cmd_status;
	char		**token;

	cmd_status = get_command();
	if (cmd_status == GET_CMD_ERROR)
		exit(EXIT_FAILURE);
	if (cmd_status == GET_CMD_EXIT || cmd_status == GET_CMD_EOF)
	{
		if (g_bash->input)
			free(g_bash->input);
		if (cmd_status == GET_CMD_EOF)
			printf("exit\n");
		return (SOURCE_EXIT);
	}
	if ((token = cmd_split(g_bash->input)) == NULL)
		return (GET_CMD_ERROR);
	sp2cmd(token);
	free_token(token, MAX_TOKEN);
	return (SOURCE_OK);
}

static void		init_bash(t_bash *bash)
{
	if (bash == NULL)
		return ;
	bash->input = NULL;
	bash->token = NULL;
}

int				main(void)
{
	t_bash		bash;

	init_bash(&bash);
	g_bash = &bash;
	while (TRUE)
	{
		print_prompt(PS1);
		if (get_source() == SOURCE_EXIT)
			break ;
		if (g_bash->input != NULL && ft_strlen(g_bash->input) != 0)
			exec_cmd(g_bash->cmd);
		cmd_end_free();
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:05:59 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/15 01:00:31 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_source(void)
{
	char	**token;
	int		cmd_status;

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
	g_bash->cmd.token = token;
	return (SOURCE_OK);
}

static void	init_bash(char **argv, char **envp)
{
	g_bash->input = NULL;
	g_bash->token = NULL;
	g_bash->execute_name = argv[0];
	g_bash->envlst = envlst_init(envp);
	g_bash->path = path_init(g_bash->envlst);
}

int			main(int argc, char **argv, char **envp)
{
	t_bash	bash;

	g_bash = &bash;
	init_bash(argv, envp);
	while (TRUE)
	{
		print_prompt(PS1);
		if (get_source() == SOURCE_EXIT)
			break ;
		if (g_bash->input != NULL && ft_strlen(g_bash->input) != 0)
			exec(g_bash->cmd);
		cmd_end_free();
	}
	envlst_free(g_bash->envlst);
	free_split(g_bash->path, MAX_SPLIT);
	(void)argc;
}

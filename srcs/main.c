/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:05:59 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/18 17:08:44 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_source(void)
{
	t_list	*token_lst;
	int		cmd_status;

	cmd_status = get_command();
	if (cmd_status == GET_CMD_ERROR)
		exit(EXIT_FAILURE);
	if (cmd_status == GET_CMD_EOF)
	{
		if (g_bash->input)
			free(g_bash->input);
		ft_printf("exit\n");
		return (SOURCE_EXIT);
	}
	token_lst = NULL;
	tokenlst_init(&token_lst, g_bash->input);
	sp2cmd(token_lst);
	free_lst(token_lst);
	return (SOURCE_OK);
}

static void	init_bash(char **argv, char **envp)
{
	g_bash->input = NULL;
	g_bash->token = NULL;
	g_bash->cmd.arg = NULL;
	g_bash->cmd.name = NULL;
	g_bash->cmd.token = NULL;
	g_bash->execute_name = argv[0];
	g_bash->envlst = envlst_init(envp);
	g_bash->home = ft_strdup(envlst_get(g_bash->envlst, "HOME")->val);
	g_bash->path = path_init(g_bash->envlst);
	g_envlst_first_wrong = (t_envlst *)malloc_safe(sizeof(t_envlst));
	g_envlst_first_wrong->name = NULL;
	g_envlst_first_wrong->val = NULL;
	g_envlst_first_wrong->next = NULL;
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
		if (g_bash->cmd.name != NULL)
			exec(g_bash->cmd);
		cmd_end_free();
	}
	envlst_free(g_bash->envlst);
	free_split(g_bash->path, MAX_SPLIT);
	free(g_envlst_first_wrong);
	(void)argc;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:05:59 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/22 14:38:07 by sunpark          ###   ########.fr       */
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
	if (cmdlst_init(token_lst) == FALSE)
		return (SOURCE_TOKEN_ERR);
	// sp2cmd(token_lst);
	// free_lst(token_lst);
	return (SOURCE_OK);
}

static void	init_bash(char **argv, char **envp)
{
	g_bash->input = NULL;
	g_bash->token = NULL;
	g_bash->execute_name = argv[0];
	g_bash->cmdlst = NULL;
	g_bash->envlst = envlst_init(envp);
	g_bash->home = ft_strdup(envlst_get(g_bash->envlst, "HOME")->val);
	g_bash->path = path_init(g_bash->envlst);
	g_envlst_first_wrong = (t_envlst *)malloc_safe(sizeof(t_envlst));
	g_envlst_first_wrong->name = NULL;
	g_envlst_first_wrong->val = NULL;
	g_envlst_first_wrong->next = NULL;
}

void		print_cmdlst()
{
	t_cmdlst	*lst;
	t_cmd		*cmd;

	lst = g_bash->cmdlst;
	while (lst)
	{
		cmd = lst->data;
		ft_printf("name : %s\n", cmd->name);
		if (cmd->arg)
			ft_printf("args[0] : %s\n", cmd->arg[0]);
		lst = lst->next;
	}
}

int			main(int argc, char **argv, char **envp)
{
	int		status;
	t_bash	bash;

	g_bash = &bash;
	init_bash(argv, envp);
	while (TRUE)
	{
		print_prompt(PS1);
		if ((status = get_source()) == SOURCE_EXIT)
			break ;
		else if (status == SOURCE_OK)
			print_cmdlst();
		cmd_end_free();
	}
	envlst_free(g_bash->envlst);
	free_split(g_bash->path, MAX_SPLIT);
	free(g_envlst_first_wrong);
	(void)argc;
}

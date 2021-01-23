/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:05:59 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/24 06:12:24 by hyukim           ###   ########.fr       */
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
		free_str(&g_bash->input);
		ft_printf("exit\n");
		return (SOURCE_EXIT);
	}
	token_lst = NULL;
	tokenlst_init(&token_lst, g_bash->input);
	if (token_lst == NULL)
		return (SOURCE_EMPTY);
	if (get_token_kind((char *)(token_lst->content)) == TOKEN_PIPE ||
			get_token_kind((char *)(token_lst->content)) == TOKEN_SEMI)
	{
		throw_token_error((char *)(token_lst->content));
		free_lst(token_lst);
		return (SOURCE_TOKEN_ERR);
	}
	return (cmdlst_init(token_lst) ? SOURCE_OK : SOURCE_TOKEN_ERR);
}

static void	init_sp(void)
{
	g_sp[0] = ft_strdup(" ");
	g_sp[1] = ft_strdup(">>");
	g_sp[2] = ft_strdup("<");
	g_sp[3] = ft_strdup(">");
	g_sp[4] = ft_strdup("|");
	g_sp[5] = ft_strdup(";");
	g_sp[6] = NULL;
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
	g_bash->forked = FALSE;
	g_envlst_first_wrong = (t_envlst *)malloc_safe(sizeof(t_envlst));
	g_envlst_first_wrong->name = NULL;
	g_envlst_first_wrong->val = NULL;
	g_envlst_first_wrong->next = NULL;
	g_bash->exit_status = (t_envlst *)malloc_safe(sizeof(t_envlst));
	g_bash->exit_status->name = "?";
	g_bash->exit_status->next = NULL;
	g_bash->exit_status->val = "";
	g_bash->note = NULL;
	g_bash->quote = '\0';
	init_sp();
}

int			main(int argc, char **argv, char **envp)
{
	int		status;
	t_bash	bash;

	g_bash = &bash;
	bind_signal();
	init_bash(argv, envp);
	while (TRUE)
	{
		print_prompt(PS1);
		if ((status = get_source()) == SOURCE_EXIT)
			break ;
		else if (status == SOURCE_OK)
			exec_cmdlst();
		cmd_end_free();
	}
	envlst_free(g_bash->envlst);
	free_split(g_bash->path, MAX_SPLIT);
	free(g_envlst_first_wrong);
	free(g_bash->exit_status);
	free_str(&g_bash->home);
	(void)argc;
}

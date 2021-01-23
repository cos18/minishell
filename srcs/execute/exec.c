/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:41:36 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/23 14:29:44 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		exec_outside(t_cmd cmd)
{
	char		*path_name;
	char		**envlst_char;

	path_name = cmd_get_path_join(g_bash->path, cmd.name);
	envlst_char = envlst_to_char(g_bash->envlst);
	execve(path_name, cmd.token, envlst_char);
	free(path_name);
	free_split(envlst_char, MAX_SPLIT);
	if (errno == 14)
		throw_custom_desc_error(cmd.name, "command not found", FALSE);
	else
		throw_error(cmd.name, ERRNO_DEFAULT, FALSE);
	exit(127);
}

static void		exec_fork_cmd(t_cmd cmd)
{
	if (cmd.name == NULL)
		return ;
	if (ft_strequ(cmd.name, "echo"))
		ft_echo(cmd);
	else if (ft_strequ(cmd.name, "cd"))
		ft_cd(cmd);
	else if (ft_strequ(cmd.name, "pwd"))
		ft_pwd();
	else if (ft_strequ(cmd.name, "export"))
		ft_export(cmd.arg, &(g_bash->envlst), &(g_bash->path));
	else if (ft_strequ(cmd.name, "unset"))
		ft_unset(cmd, &(g_bash->envlst), &(g_bash->path));
	else if (ft_strequ(cmd.name, "env"))
		ft_env(g_bash->envlst);
	else if (ft_strequ(cmd.name, "exit"))
		exit(0);
	else
		exec_outside(cmd);
	exit(0);
}

static void		exec_fork(t_cmd cmd)
{
	int			wc;
	int			pid;

	pid = fork();
	if (pid < 0)
		throw_error(cmd.name, ERRNO_DEFAULT, TRUE);
	else if (pid == 0)
		exec_fork_cmd(cmd);
	else
		wc = wait(NULL);
}

static void		exec(t_cmdlst *lst)
{
	t_cmd		cmd;
	int			status;

	cmd = *(lst->data);
	if (ft_strequ(cmd.name, "exit"))
	{
		if ((status = ft_exit(cmd)) != EXIT_TOO_MANY_ARGS)
			exit(status);
	}
	if (ft_strequ(cmd.name, "cd"))
		ft_cd(cmd);
	else if (ft_strequ(cmd.name, "export"))
		ft_export(cmd.arg, &(g_bash->envlst), &(g_bash->path));
	else if (ft_strequ(cmd.name, "unset"))
		ft_unset(cmd, &(g_bash->envlst), &(g_bash->path));
	else
		exec_fork(cmd);
}

void			exec_cmdlst(void)
{
	int			is_stdout_change;
	int			is_stdin_change;
	t_cmdlst	*cmd_now;
	t_cmdlst	*now;

	now = g_bash->cmdlst;
	while (now)
	{
		is_stdout_change = FALSE;
		is_stdin_change = FALSE;
		cmd_now = now;
		while (now && get_token_kind(now->data->name) != TOKEN_SEMI)
		{
			if (handle_redir(now, &is_stdout_change, &is_stdin_change) == FALSE)
				break ;
			now = now->next;
		}
		if (now && get_token_kind(now->data->name) != TOKEN_SEMI)
			break ;
		exec(cmd_now);
		if (now)
			now = now->next;
		change_to_std(is_stdout_change, is_stdin_change);
	}
	change_to_std(is_stdout_change, is_stdin_change);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:41:36 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/23 18:10:45 by sunpark          ###   ########.fr       */
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
	int			status;

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
	{
		if ((status = ft_exit(cmd)) != EXIT_TOO_MANY_ARGS)
			exit(status);
	}
	else
		exec_outside(cmd);
	errno = 0;
	exit(0);
}

static void		exec_fork(t_cmdlst *lst)
{
	t_cmd		cmd;
	int			wc;
	int			pid;
	int			exits;

	cmd = *(lst->data);
	pid = fork();
	if (pid < 0)
		throw_error(cmd.name, ERRNO_DEFAULT, TRUE);
	else if (pid == 0)
	{
		g_bash->forked = TRUE;
		exec_fork_cmd(cmd);
	}
	else
	{
		g_bash->forked = TRUE;
		wc = waitpid(pid, &exits, 0);
		errno = WEXITSTATUS(exits);
		g_bash->forked = FALSE;
	}
}

static void		exec(t_cmdlst *lst, t_cmdlst *pipe_lst)
{
	t_cmd		cmd;
	int			status;

	cmd = *(lst->data);
	if (open_inout(cmd) == FALSE)
		return ;
	if (ft_strequ(cmd.name, "exit"))
	{
		if ((status = ft_exit(cmd)) != EXIT_TOO_MANY_ARGS)
			exit(status);
	}
	else if (ft_strequ(cmd.name, "cd"))
		ft_cd(cmd);
	else if (ft_strequ(cmd.name, "export"))
		ft_export(cmd.arg, &(g_bash->envlst), &(g_bash->path));
	else if (ft_strequ(cmd.name, "unset"))
		ft_unset(cmd, &(g_bash->envlst), &(g_bash->path));
	else if (ft_strequ(cmd.name, "exit"))
		errno = 1;
	else
		exec_fork(lst);
	close_inout(cmd);
	if (pipe_lst != NULL)
		ft_printf("%s", pipe_lst->data->name);
}

void			exec_cmdlst(void)
{
	t_cmdlst	*cmd_now;
	t_cmdlst	*cmd_pipe;
	t_cmdlst	*now;

	now = g_bash->cmdlst;
	while (now)
	{
		cmd_pipe = NULL;
		cmd_now = now;
		while (now && get_token_kind(now->data->name) != TOKEN_SEMI)
		{
			if (get_token_kind(now->data->name) == TOKEN_PIPE)
				cmd_pipe = now;
			if (cmd_pipe == NULL && handle_redir(cmd_now, now) == FALSE)
				break ;
			now = now->next;
		}
		if (cmd_now->data->in == -1 || cmd_now->data->out == -1)
			break ;
		if (get_token_kind(cmd_now->data->name) == TOKEN_DEFAULT)
			exec(cmd_now, cmd_pipe);
		else
			close_inout(*(cmd_now->data));
		if (now)
			now = now->next;
	}
}

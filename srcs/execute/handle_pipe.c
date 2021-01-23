/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 01:07:20 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/24 03:15:48 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		set_pipe_fd(t_cmd cmd, int *ppip, int *npip)
{
	if (npip && npip[0] != -10)
	{
		dup2(npip[1], STDOUT);
		close(npip[1]);
		close(npip[0]);
	}
	if (ppip && ppip[0] != -10)
	{
		dup2(ppip[0], STDIN);
		close(ppip[1]);
		close(ppip[0]);
	}
	if (cmd.in != STDIN)
		dup2(cmd.in, STDIN);
	if (cmd.out != STDOUT)
		dup2(cmd.out, STDOUT);
}

static void		exec_pipe_recur3(t_cmdlst *pcmd, int *npip)
{
	t_cmdlst	*now_cmd;
	t_cmdlst	*cmd_pipe;

	pcmd = pcmd->next;
	cmd_pipe = NULL;
	now_cmd = pcmd;
	while (pcmd && get_token_kind(pcmd->data->name) != TOKEN_SEMI)
	{
		if (get_token_kind(pcmd->data->name) == TOKEN_PIPE)
		{
			cmd_pipe = pcmd;
			break ;
		}
		if (handle_redir(now_cmd, pcmd) == FALSE)
			break ;
		pcmd = pcmd->next;
	}
	if (now_cmd->data->in == -1 || now_cmd->data->out == -1)
		return ;
	exec_pipe_recur(now_cmd, cmd_pipe, npip);
}

static void		exec_pipe_recur2(t_cmdlst *pcmd, int *ppip, int *npip, int pid)
{
	int			ws;
	int			exits;

	g_bash->forked = TRUE;
	if (ppip)
	{
		close(ppip[0]);
		close(ppip[1]);
	}
	if (pcmd)
		exec_pipe_recur3(pcmd, npip);
	ws = waitpid(pid, &exits, 0);
	errno = WEXITSTATUS(exits);
	g_bash->forked = FALSE;
}

void			exec_pipe_recur(t_cmdlst *lst, t_cmdlst *pipe_lst, int *ppip)
{
	int			npip[2];
	t_cmd		cmd;
	int			pid;

	cmd = *(lst->data);
	if (pipe_lst)
		pipe(npip);
	else
		npip[0] = -10;
	pid = fork();
	if (pid < 0)
		throw_error(cmd.name, ERRNO_DEFAULT, TRUE);
	else if (pid == 0)
	{
		g_bash->forked = TRUE;
		if (get_token_kind(lst->data->name) == TOKEN_DEFAULT)
		{
			set_pipe_fd(cmd, ppip, npip);
			exec_fork_cmd(cmd);
		}
		else
			close_inout(cmd);
	}
	else
		exec_pipe_recur2(pipe_lst, ppip, npip, pid);
}

void			exec_pipe(t_cmdlst *lst, t_cmdlst *pipe_lst)
{
	int			std_dup[2];
	int			locate;

	locate = -1;
	while (++locate)
		std_dup[locate] = dup(locate);
	exec_pipe_recur(lst, pipe_lst, NULL);
	locate = -1;
	while (++locate)
		dup2(std_dup[locate], locate);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:51:56 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/23 16:03:23 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_redir_in(t_cmdlst *now_cmd, t_cmdlst *now)
{
	int	fd;

	if ((fd = open(now->data->arg[0], O_RDONLY)) == -1)
	{
		if (fd != -1)
			close(fd);
		throw_error(now->data->arg[0], ERRNO_DEFAULT, FALSE);
		now_cmd->data->in = -1;
		return (FALSE);
	}
	if (now_cmd->data->in != STDIN)
		close(now_cmd->data->in);
	now_cmd->data->in = fd;
	return (TRUE);
}

int		handle_redir(t_cmdlst *now_cmd, t_cmdlst *now)
{
	int	kind;
	int	fd;
	int	flags;

	kind = get_token_kind(now->data->name);
	if (kind == TOKEN_REDIR_IN)
		return (handle_redir_in(now_cmd, now));
	if (kind != TOKEN_REDIR_OUT && kind != TOKEN_REDIR_OUT_DUP)
		return (TRUE);
	flags = (kind == TOKEN_REDIR_OUT ? (O_TRUNC | O_RDWR | O_CREAT)
									: (O_RDWR | O_CREAT | O_APPEND));
	fd = open(now->data->arg[0], flags, 0777);
	if (fd == -1)
	{
		throw_error(now->data->arg[0], ERRNO_DEFAULT, FALSE);
		now_cmd->data->out = -1;
		return (FALSE);
	}
	if (now_cmd->data->out != STDOUT)
		close(now_cmd->data->out);
	now_cmd->data->out = fd;
	return (TRUE);
}

int		open_inout(t_cmd cmd)
{
	if (cmd.in != STDIN)
	{
		if (dup2(STDIN, STDIN_TMP) == -1 || dup2(cmd.in, STDIN) == -1)
		{
			throw_error(cmd.arg[0], ERRNO_DEFAULT, FALSE);
			close(cmd.in);
			if (cmd.out != STDOUT)
				close(cmd.out);
			return (FALSE);
		}
	}
	if (cmd.out != STDOUT)
	{
		if (dup2(STDOUT, STDOUT_TMP) == -1 || dup2(cmd.out, STDOUT) == -1)
		{
			throw_error(cmd.arg[0], ERRNO_DEFAULT, FALSE);
			close(cmd.out);
			if (cmd.in != STDOUT)
				dup2(STDIN_TMP, STDIN);
			return (FALSE);
		}
	}
	return (TRUE);
}

void	close_inout(t_cmd cmd)
{
	if (cmd.in != STDIN)
		dup2(STDIN_TMP, STDIN);
	if (cmd.out != STDOUT)
		dup2(STDOUT_TMP, STDOUT);
}

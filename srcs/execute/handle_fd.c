/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:51:56 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/23 14:28:49 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_to_std(int is_stdout_change, int is_stdin_change)
{
	if (is_stdout_change)
		dup2(STDOUT_TMP, STDOUT);
	if (is_stdin_change)
		dup2(STDIN_TMP, STDIN);
}

int		handle_redir_in(t_cmdlst *now, int *is_stdin_change)
{
	int	fd;

	if (*is_stdin_change == FALSE)
		dup2(STDIN, STDIN_TMP);
	*is_stdin_change = TRUE;
	if ((fd = open(now->data->arg[0], O_RDONLY)) == -1 || dup2(fd, STDIN) == -1)
	{
		if (fd != -1)
			close(fd);
		throw_error(now->data->arg[0], ERRNO_DEFAULT, FALSE);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

int		handle_redir(t_cmdlst *now, int *is_stdout_change, int *is_stdin_change)
{
	int	kind;
	int	fd;
	int	flags;

	kind = get_token_kind(now->data->name);
	if (kind == TOKEN_REDIR_IN)
		return (handle_redir_in(now, is_stdin_change));
	if (kind != TOKEN_REDIR_OUT && kind != TOKEN_REDIR_OUT_DUP)
		return (TRUE);
	if (*is_stdout_change == FALSE)
		dup2(STDOUT, STDOUT_TMP);
	*is_stdout_change = TRUE;
	flags = (kind == TOKEN_REDIR_OUT ? (O_TRUNC | O_RDWR | O_CREAT)
									: (O_RDWR | O_CREAT | O_APPEND));
	fd = open(now->data->arg[0], flags, 0777);
	if (fd == -1 || dup2(fd, STDOUT) == -1)
	{
		if (fd != -1)
			close(fd);
		throw_error(now->data->arg[0], ERRNO_DEFAULT, FALSE);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

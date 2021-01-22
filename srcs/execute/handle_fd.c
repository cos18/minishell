/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:51:56 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/22 18:47:38 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_redir_out(t_cmdlst *now, int *is_fd_change)
{
	int	kind;
	int	fd;
	int	flags;

	kind = get_token_kind(now->data->name);
	if (kind != TOKEN_REDIR_OUT && kind != TOKEN_REDIR_OUT_DUP)
		return (TRUE);
	if (*is_fd_change == FALSE)
	{
		*is_fd_change = TRUE;
		dup2(STDOUT, STDOUT_TMP);
	}
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

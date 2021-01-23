/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:25:07 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/23 17:29:28 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTE_H
# define MINISHELL_EXECUTE_H

# include "minishell_token.h"

void	exec_cmdlst(void);

void	init_pipe_cmd(t_cmdlst *lst, t_cmdlst *pipe_lst);

void	close_inout_fd(t_cmdlst *now_cmd);
int		handle_redir_in(t_cmdlst *now_cmd, t_cmdlst *now);
int		handle_redir(t_cmdlst *now_cmd, t_cmdlst *now);
int		open_inout(t_cmd cmd);
void	close_inout(t_cmd cmd);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:25:07 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/23 14:35:39 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTE_H
# define MINISHELL_EXECUTE_H

# include "minishell_token.h"

void	exec_cmdlst(void);

void	change_to_std(int is_stdout_change, int is_stdin_change);
int		handle_redir_in(t_cmdlst *now, int *is_stdin_change);
int		handle_redir(t_cmdlst *now, int *is_stdout_change,
						int *is_stdin_change);

#endif

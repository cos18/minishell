/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:25:07 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/15 00:43:19 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTE_H
# define MINISHELL_EXECUTE_H

# include "minishell_token.h"

void	exec(t_cmd cmd);
void	exec_cmd(t_cmd cmd);

#endif

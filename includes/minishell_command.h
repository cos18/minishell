/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:52:01 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/11 17:21:54 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_COMMAND_H
# define MINISHELL_COMMAND_H

# include <unistd.h>
# include <string.h>
# include "minishell_token.h"

# define MAX_PATH_LEN 4096

void		ft_pwd(void);
void		ft_cd(t_cmd cmd);
#endif

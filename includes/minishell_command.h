/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:52:01 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/12 15:30:16 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_COMMAND_H
# define MINISHELL_COMMAND_H

# include <unistd.h>
# include <string.h>
# include "minishell_token.h"
# include "minishell_env.h"

void	ft_pwd(void);
void	ft_cd(t_cmd cmd);
void	ft_env(t_envlst *lst);
void	ft_unset(t_cmd cmd, t_envlst **lst);
void	ft_export(t_cmd cmd, t_envlst **lst);

#endif

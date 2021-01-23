/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:07:32 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/24 03:34:38 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <dirent.h>
# include <errno.h>
# include "libft.h"
# include "minishell_const.h"
# include "minishell_util.h"
# include "minishell_token.h"
# include "minishell_execute.h"
# include "minishell_command.h"
# include "minishell_env.h"

typedef struct	s_bash
{
	char		*execute_name;
	char		*input;
	char		**token;
	char		*home;
	t_cmdlst	*cmdlst;
	t_envlst	*envlst;
	t_envlst	*exit_status;
	char		**path;
	int			forked;
	char		*note;
}				t_bash;

t_bash			*g_bash;
t_envlst		*g_envlst_first_wrong;
char			*g_sp[7];

void			print_prompt(int ps);
int				get_command(void);

#endif

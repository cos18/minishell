/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:07:32 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/11 18:29:11 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include "minishell_const.h"
# include "minishell_util.h"
# include "minishell_token.h"
# include "minishell_execute.h"

typedef struct	s_bash
{
	char		*execute_name;
	char		*input;
	t_cmd		cmd;
	char		**token;
}				t_bash;

t_bash			*g_bash;

void			print_prompt(int ps);
int				get_command(void);

void			cmd_end_free(void);
void			free_cmd(t_cmd *cmd);
int				free_token(char **sep, int word_locate);

#endif

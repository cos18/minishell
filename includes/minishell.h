/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:07:32 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/08 19:16:25 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */ 
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "minishell_const.h"
# include "minishell_token.h"

typedef struct	s_bash
{
	char		*input;
	t_cmd		cmd;
	char		**token;
}				t_bash;

t_bash			*g_bash;

void			print_prompt(int ps);
int				get_command(void);

void			cmd_end_free(void);
int				free_token(char **sep, int word_locate);

#endif

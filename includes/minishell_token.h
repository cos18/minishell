/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 15:50:51 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/22 21:13:05 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TOKEN_H
# define MINISHELL_TOKEN_H

# include <errno.h>

typedef struct	s_cmd
{
	char		*name;
	char		**arg;
	char		**token;
}				t_cmd;

char			**cmd_split(char *s);

void			tokenlst_init(t_list **lst, char *input);

void			sp2cmd(t_list *lst);

int				is_split(char *in, char *sp[]);
int				is_cur_sp(char *in, char *sp[]);
void			handle_sp(char **start, char *end, t_list **list);
void			handle_sp2(char **start, char *end, t_list **list);
#endif

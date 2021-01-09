/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 15:50:51 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/09 18:49:34 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TOKEN_H
# define MINISHELL_TOKEN_H

# include <errno.h>

typedef struct	s_cmd
{
	char		*name;
	char		**arg;
}				t_cmd;

char			**cmd_split(char *s);

size_t			ft_sp_size(char **sp);
void			sp2cmd(char **sp);
void			exec_cmd(t_cmd cmd);
int				ft_strequ(char *s1, char *s2);
#endif

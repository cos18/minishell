/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 15:50:51 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/11 18:26:10 by sunpark          ###   ########.fr       */
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

char			**token_cpy(char **token);

size_t			ft_sp_size(char **sp);
void			sp2cmd(char **sp);
int				ft_strequ(char *s1, char *s2);
#endif

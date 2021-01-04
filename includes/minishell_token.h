/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 15:50:51 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/05 00:35:08 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TOKEN_H
# define MINISHELL_TOKEN_H

# include <errno.h>

typedef struct	s_source
{
	char		*buf;
	long		bufsize;
	long		curpos;
}				t_source;

int				free_token(char **sep, int word_locate);
char			**cmd_split(char const *s);

#endif

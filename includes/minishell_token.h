/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 15:50:51 by sunpark           #+#    #+#             */
/*   Updated: 2020/12/20 17:15:39 by sunpark          ###   ########.fr       */
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

void			src_set();
void			src_unget_char(t_source *src);
char			src_next_char(t_source *src);
char			src_peek_char(t_source *src);
void			src_skip_spaces(t_source *src);

#endif

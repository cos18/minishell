/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 15:55:30 by sunpark           #+#    #+#             */
/*   Updated: 2020/12/20 17:15:49 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		src_set()
{
	g_bash->src.bufsize = ft_strlen(g_bash->src.buf);
	g_bash->src.curpos = SRC_INIT_POS;
}

void		src_unget_char(t_source *src)
{
	if (src->curpos < 0)
		return ;
	(src->curpos)--;
}

char		src_next_char(t_source *src)
{
	if (!src || !(src->buf))
	{
		errno = ENODATA;
		return (SRC_ERRCHAR);
	}
	if (src->curpos == SRC_INIT_POS)
		src->curpos = -1;
	src->curpos += 1;
	if (src->curpos >= src->bufsize)
	{
		src->curpos = src->bufsize;
		return (SRC_EOF);
	}
	return (src->buf[src->curpos]);
}

char		src_peek_char(t_source *src)
{
	long	pos;

	if (!src || !(src->buf))
	{
		errno = ENODATA;
		return (SRC_ERRCHAR);
	}
	pos = src->curpos;
	if (pos == SRC_INIT_POS)
		pos++;
	pos++;
	if (pos >= src->bufsize)
		return (SRC_EOF);
	return (src->buf[pos]);
}

void		src_skip_spaces(t_source *src)
{
	char	c;

	if (!src || !(src->buf))
		return ;
	while (((c = src_peek_char(src)) != SRC_EOF) && (c == ' ' || c == '\t'))
		src_next_char(src);
}

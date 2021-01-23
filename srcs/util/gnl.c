/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:43:14 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/23 17:15:34 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_nextchar(char *str, int c)
{
	size_t	i;

	if (str == 0)
		return (NULL);
	if (c == 0)
		return ((char *)str + ft_strlen(str));
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}

static void	handle_eof(char **note, char buff[2], int byte, char **tmp)
{
	*tmp = (*note == NULL ? ft_strndup(buff, byte) :
		ft_strjoin(*note, buff));
	if (*note != 0)
		free(*note);
	*note = *tmp;
}

static int	handle_line(char **line, char **note, char *nl_here)
{
	char	*tmp;

	if (nl_here != NULL)
	{
		*line = ft_strndup(*note, nl_here - *note);
		tmp = ft_strndup(nl_here + 1, ft_strlen(nl_here + 1));
		free(*note);
		*note = tmp;
		return (1);
	}
	if (*note != NULL)
	{
		*line = *note;
		*note = NULL;
	}
	else
		*line = ft_strndup("", 1);
	return (0);
}

int			gnl(int fd, char **line)
{
	static char	*note[5000];
	char		buff[2];
	int			byte;
	char		*tmp;
	char		*nl_here;

	if (fd < 0 || line == NULL)
		return (-1);
	byte = 0;
	while (((nl_here = ft_nextchar(note[fd], '\n')) == 0
			&& (byte = read(fd, buff, 1)) > 0)
			|| (byte == 0 && note[fd] != 0 && note[fd][0] != '\0'))
	{
		if (byte == 0 && note[fd][0] == '\0')
			return (-1);
		if (byte == 0)
			write(fd, "  \b\b", 4);
		else
		{
			buff[byte] = 0;
			handle_eof(&note[fd], buff, byte, &tmp);
		}
	}
	return (handle_line(line, &note[fd], nl_here));
}

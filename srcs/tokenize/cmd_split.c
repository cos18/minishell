/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:01:29 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/04 17:59:25 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_token(char const *s)
{
	int		result;
	int		is_word;
	char	quote;

	result = 0;
	is_word = 0;
	quote = '\0';
	while (*s)
	{
		if (is_word == 0 && !ft_isblank(*s))
			is_word = 1;
		if (is_word && ft_isblank(*s) && quote == '\0')
		{
			result++;
			is_word = 0;
		}
		if ((*s == '\'' || *s == '\"') && (quote == '\0'))
			quote = *s;
		if ((*s == '\'' || *s == '\"') && (quote == *s))
			quote = '\0';
		s++;
	}
	if (is_word)
		result++;
	return (result);
}

static char	*cmd_substr(char const *s, size_t len)
{
	char	*result;
	char	*tmp;
	size_t	locate;
	size_t	totsize;
	char	quote;

	totsize = (ft_strlen(s) > len) ? len : ft_strlen(s);
	result = (char *)malloc(totsize + 1);
	if (result)
	{
		locate = -1;
		tmp = result;
		while (++locate < totsize)
		{
			if ((s[locate] == '\'' || s[locate] == '\"') && (quote == '\0'))
				quote = s[locate];
			if ((s[locate] == '\'' || s[locate] == '\"') && (quote == *s))
				quote = '\0';
			if (quote != s[locate])
				*(tmp++) = s[locate];
		}
		*(tmp++) = '\0';
	}
	return (result);
}

static int	free_strs(char **sep, int word_locate)
{
	int	locate;

	locate = -1;
	while (++locate < word_locate - 1)
		free(sep[locate]);
	return (1);
}

static int	get_sep_token(char **sep, char const *s)
{
	int		word_size;
	int		word_locate;
	char	*start;
	char	quote;

	word_size = 0;
	word_locate = 0;
	quote = '\0';
	while (*s)
	{
		if (word_size == 0 && !ft_isblank(*s))
			start = (char *)s;
		if (word_size && ft_isblank(*s) && quote == '\0')
		{
			sep[word_locate] = cmd_substr(start, word_size);
			if (sep[word_locate++] == NULL)
				return (free_strs(sep, word_locate));
			word_size = 0;
		}
		if ((*s == '\'' || *s == '\"') && (quote == '\0'))
			quote = *s;
		if ((*s == '\'' || *s == '\"') && (quote == *s))
			quote = '\0';
		if (quote != '\0' || !ft_isblank(*s))
			word_size++;
		s++;
	}
	if (word_size)
		sep[word_locate++] = cmd_substr(start, word_size);
	sep[word_locate] = NULL;
	return (0);
}

char		**cmd_split(char const *s)
{
	int		words;
	char	**result;

	if (!s)
		return (NULL);
	words = count_token(s);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (result && get_sep_token(result, s))
	{
		free(result);
		result = NULL;
	}
	return (result);
}

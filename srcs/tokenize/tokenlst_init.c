/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlst_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:49:00 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/22 23:43:44 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		handle_env(char *token, int *locate, char **start)
{
	t_envlst	*env;
	char		*val;
	char		*tmp;

	if ((env = get_env_in_token(start)) == g_envlst_first_wrong)
	{
		token[(*locate)++] = **start;
		return ;
	}
	if (env == NULL || env->val == NULL)
		return ;
	if (ft_strequ(*start, "?"))
	{
		tmp = ft_itoa(errno);
		val = tmp;
	}
	else
		val = env->val;
	while (*val)
	{
		token[(*locate)++] = *val;
		val++;
	}
	if (ft_strequ(env->name, "?"))
		free(tmp);
}

static void		handle_backslash(char *token, int *locate, char **start,
									char quote)
{
	if ((*(*start + 1) != '\n' || quote == '\"'))
		token[(*locate)++] = *(++(*start));
	else
		++(*start);
}

static void		set_token(char *token, char *start, char *end)
{
	char		quote;
	char		*is;
	int			locate;

	quote = '\0';
	is = start;
	locate = 0;
	while (start != end)
	{
		if ((*start == '\'' || check_double_quote(is, start))
				&& (quote == '\0'))
			quote = *start;
		else if ((*start == '\'' || check_double_quote(is, start))
				&& (quote == *start))
			quote = '\0';
		else if (*start == '$' && quote != '\'')
			handle_env(token, &locate, &start);
		else if (*start == '\\' && quote != '\'')
			handle_backslash(token, &locate, &start, quote);
		else
			token[locate++] = *start;
		start++;
	}
	token[locate] = '\0';
}

static void		add_token(t_list **lst, char **start, char *end)
{
	t_list		*tokenlst;
	char		*token;
	char		*now;
	int			env_len;

	now = *start;
	env_len = 0;
	while (now != end)
	{
		if (*now == '$')
			env_len += check_env_len(&now);
		now++;
	}
	token = (char *)malloc_safe(sizeof(char) * (end - *start + env_len + 1));
	set_token(token, *start, end);
	if ((tokenlst = ft_lstnew((void *)token)) == NULL)
		throw_error("Malloc failed", ERRNO_DEFAULT, TRUE);
	ft_lstadd_back(lst, tokenlst);
	*start = NULL;
}

void			tokenlst_init(t_list **lst, char *input)
{
	char		quote;
	char		*start;
	char		*is;

	quote = '\0';
	start = NULL;
	is = input;
	while (*input)
	{
		if (start == NULL && !ft_isblank(*input))
			start = input;
		if (start && ft_isblank(*input) && quote == '\0'
				&& (is == input || *(input - 1) != '\\'))
			add_token(lst, &start, input);
		if ((*input == '\'' || check_double_quote(is, input))
				&& (quote == '\0'))
			quote = *input;
		else if ((*input == '\'' || check_double_quote(is, input))
				&& (quote == *input))
			quote = '\0';
		input++;
	}
	if (start)
		add_token(lst, &start, input);
}

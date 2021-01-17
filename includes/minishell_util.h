/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:50:24 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/17 20:55:56 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTIL_H
# define MINISHELL_UTIL_H

# include "minishell_token.h"

void	cmd_end_free(void);
void	free_cmd(t_cmd *cmd);
int		free_split(char **sep, int word_locate);
void	free_lst(t_list *lst);

void	throw_error(char *message, int pnum, int is_end);
void	throw_custom_desc_error(char *message, char *desc, int is_end);
void	*malloc_safe(size_t size);

int		ft_strequ(char *s1, char *s2);
size_t	ft_sp_size(char **sp);
int		check_equation(int *locate, char *equation);
char	*strjoin_free_a(char *a, char *b);
int		check_double_quote(char *is, char *input);

void	sighandler(int signo);
#endif

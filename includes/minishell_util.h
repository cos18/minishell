/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:50:24 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/08 17:13:13 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTIL_H
# define MINISHELL_UTIL_H

void	cmd_end_free(void);
int		free_token(char **sep, int word_locate);

void	exec_token(void);

void	throw_error(char *message, int pnum);
void	*malloc_safe(size_t size);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:50:24 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/11 18:36:08 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTIL_H
# define MINISHELL_UTIL_H

# include "minishell_token.h"

void	cmd_end_free(void);
void	free_cmd(t_cmd *cmd);
int		free_token(char **sep, int word_locate);

void	throw_error(char *message, int pnum, int is_end);
void	*malloc_safe(size_t size);

#endif

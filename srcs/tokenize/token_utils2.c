/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:05:22 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/23 18:31:17 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd		*cmd_init(char *name)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc_safe(sizeof(t_cmd));
	cmd->name = strdup_with_home(name);
	cmd->arg = NULL;
	cmd->token = NULL;
	cmd->in = STDIN;
	cmd->out = STDOUT;
	return (cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:05:59 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/28 23:30:22 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(void)
{
	char	*cmd;
	int		cmd_status;

	while (TRUE)
	{
		cmd = NULL;
		print_prompt(PS1);
		cmd_status = get_command(&cmd);
		if (cmd_status == GET_CMD_ERROR)
			exit(EXIT_FAILURE);
		if (cmd_status == GET_CMD_EXIT || cmd_status == GET_CMD_EOF)
		{
			if (cmd)
				free(cmd);
			if (cmd_status == GET_CMD_EOF)
				printf("exit\n");
			break ;
		}
		if (cmd != NULL && ft_strlen(cmd) != 0)
			ft_printf("%s\n", cmd);
		free(cmd);
	}
}

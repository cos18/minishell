/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:05:59 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/27 23:40:45 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(void)
{
	char	*cmd;
	int		gnl_result;

	while (TRUE)
	{
		print_prompt();
		gnl_result = get_next_line(0, &cmd);
		if (gnl_result == GNL_ERROR)
			exit(EXIT_SUCCESS);
		if (gnl_result == GNL_READ_EOF || ft_strncmp(cmd, "exit", 5) == 0)
		{
			if (gnl_result == GNL_READ_EOF)
				ft_printf("exit\n");
			free(cmd);
			break;
		}
		if (ft_strlen(cmd) == 0)
		{
			free(cmd);
			continue;
		}
		ft_printf("%s\n", cmd);
		free(cmd);
	}
	exit(EXIT_SUCCESS);
}

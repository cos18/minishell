/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_const.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:23:18 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/12 02:36:47 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CONST_H
# define MINISHELL_CONST_H

# define STDOUT 1
# define STDERR 2

# define TRUE 1
# define FALSE 0

# define ERRNO_DEFAULT -1

# define PS1 1
# define PS2 2

# define GET_CMD_ERROR -1
# define GET_CMD_EOF 0
# define GET_CMD_READ 1
# define GET_CMD_EXIT 2

# define SOURCE_OK 0
# define SOURCE_EXIT 1

# define MAX_TOKEN 10000

# define MAX_PATH_LEN 4096
#endif

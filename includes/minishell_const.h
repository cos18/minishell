/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_const.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:23:18 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/24 03:47:31 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CONST_H
# define MINISHELL_CONST_H

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define STDIN_TMP 200
# define STDOUT_TMP 201

# define TRUE 1
# define FALSE 0

# define ERRNO_DEFAULT -1

# define PS1 1
# define PS2 2

# define GET_CMD_ERROR -1
# define GET_CMD_EOF 0
# define GET_CMD_READ 1

# define SOURCE_OK 0
# define SOURCE_TOKEN_ERR 1
# define SOURCE_EMPTY 2
# define SOURCE_EXIT 3

# define MAX_SPLIT 10000000

# define TOKEN_DEFAULT 0
# define TOKEN_PIPE 1
# define TOKEN_REDIR_OUT 2
# define TOKEN_REDIR_OUT_DUP 3
# define TOKEN_REDIR_IN 4
# define TOKEN_SEMI 5

# define MAX_PATH_LEN 4096

# define ENV_PWD "PWD"
# define ENV_OLDPWD "OLDPWD"
# define ENV_PATH "PATH"
# define ENV_PATH_WITHPLUS "PATH+"

# define EXIT_TOO_MANY_ARGS -1

#endif

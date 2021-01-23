/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 15:50:51 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/23 18:07:30 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TOKEN_H
# define MINISHELL_TOKEN_H

# include <errno.h>

typedef struct		s_cmd
{
	char			*name;
	char			**arg;
	char			**token;
	int				in;
	int				out;
}					t_cmd;

t_cmd				*cmd_init(char *name);

char				**cmd_split(char *s);

void				tokenlst_init(t_list **lst, char *input);

int					is_split(char *in, char *sp[]);
int					is_cur_sp(char *in, char *sp[]);
void				handle_sp(char **start, char *end, t_list **list);
void				handle_sp2(char **start, char *end, t_list **list);
void				cnt_env_len(char **now, char *end, int *env_len);

typedef struct		s_cmdlst
{
	struct s_cmdlst	*prev;
	t_cmd			*data;
	struct s_cmdlst	*next;
}					t_cmdlst;

int					free_left_vars(t_list *tokenlst);
int					get_token_kind(char *token);
int					add_arglst_to_cmd(t_cmdlst *cmd_loc, t_list *arglst);
void				connect_redir_cmd(t_cmdlst *cmd_loc, t_cmdlst *redir_start);
void				set_cmd_token(t_cmd *cmd);

t_cmdlst			*cmdlst_new(t_cmd *cmd);
t_cmdlst			*cmdlst_add_next(t_cmdlst *lst, t_cmd *cmd);
t_cmdlst			*cmdlst_add_prev(t_cmdlst *lst, t_cmd *cmd);
t_cmdlst			*cmdlst_add_last(t_cmdlst **lst, t_cmd *cmd);
t_cmdlst			*cmdlst_get_last(t_cmdlst *lst);

int					cmdlst_init(t_list *tokenlst);

#endif

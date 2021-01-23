/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:55:14 by sunpark           #+#    #+#             */
/*   Updated: 2021/01/22 23:44:06 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ENV_H
# define MINISHELL_ENV_H

typedef struct		s_envlst
{
	char			*name;
	char			*val;
	struct s_envlst	*next;
}					t_envlst;

int					envlst_cnt(t_envlst *lst);
void				envlst_add(t_envlst **lst, char *equation);
void				envlst_append(t_envlst **lst, char *name, char *equation,
									int l);
void				envlst_del(t_envlst **lst, char *name);
char				**envlst_to_char(t_envlst *lst);

t_envlst			*envlst_init(char **envp);
t_envlst			*envlst_get(t_envlst *lst, char *name);
void				envlst_free(t_envlst *lst);
void				envlst_set_pwd(t_envlst *lst);

int					env_valid_name(char *name, int is_export);
t_envlst			*get_env_in_token(char **check);
int					check_env_len(char **check);
int					ft_int_len(long n);

char				**path_init(t_envlst *envlst);
void				reset_path(char ***path, t_envlst *envlst);
char				*cmd_get_path_join(char **path, char *name);

#endif

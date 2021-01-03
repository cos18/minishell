/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:07:37 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/04 04:09:20 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H
# include <stdlib.h>

typedef struct		s_node
{
	struct s_node	*down;
	int				content;
	struct s_node	*up;
}					t_node;

typedef struct		s_stack
{
	t_node			*base;
	t_node			*top;
	size_t			size;
}					t_stack;

t_stack				*init_stack(void);
int					stack_empty(t_stack stack);
int					stack_pop(t_stack *stack);
void				stack_push(t_stack *stack, int content);
void				free_stack(t_stack *stack);
#endif

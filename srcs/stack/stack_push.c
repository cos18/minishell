/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:24:34 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/04 04:04:42 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static t_node	*init_node(void)
{
	t_node	*node;

	if ((node = (t_node *)malloc(sizeof(t_node))) == NULL)
		return (NULL);
	node->down = NULL;
	node->up = NULL;
	node->content = 0;
	return (node);
}

void			stack_push(t_stack *stack, int content)
{
	t_node	*node;

	if (stack == NULL || (node = init_node()) == NULL)
		return ;
	node->content = content;
	if (stack->base == NULL)
	{
		stack->base = node;
		stack->top = node;
	}
	else
	{
		stack->top->up = node;
		node->down = stack->top;
		stack->top = node;
	}
	stack->size += 1;
}

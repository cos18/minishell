/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:34:46 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/04 04:21:25 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void	del_node(t_node *node)
{
	if (node == NULL)
		return ;
	node->content = 0;
	free(node);
	node = NULL;
}

int			stack_pop(t_stack *stack)
{
	int		ret;
	t_node	*tmp;

	if (stack == NULL || stack_empty(*stack))
		return (0);
	tmp = stack->top;
	ret = tmp->content;
	if (stack->size == 1)
	{
		stack->base = NULL;
		stack->top = NULL;
	}
	else
	{
		stack->top = tmp->down;
		stack->top->up = NULL;
	}
	del_node(tmp);
	stack->size -= 1;
	return (ret);
}

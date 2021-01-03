/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:44:30 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/04 03:00:19 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void		free_stack(t_stack *stack)
{
	if (stack == NULL || stack_empty(*stack))
		return ;
	while (!stack_empty(*stack))
		stack_pop(stack);
	if (stack->base)
	{
		free(stack->base);
		stack->base = NULL;
	}
	if (stack->top)
	{
		free(stack->top);
		stack->top = NULL;
	}
	free(stack);
	stack = NULL;
}

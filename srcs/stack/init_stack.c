/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyukim <hyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 02:19:23 by hyukim            #+#    #+#             */
/*   Updated: 2021/01/04 02:26:24 by hyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_stack		*init_stack(void)
{
	t_stack		*stack;

	if ((stack = (t_stack *)malloc(sizeof(t_stack))) == NULL)
		return (NULL);
	stack->base = NULL;
	stack->top = NULL;
	stack->size = 0;
	return (stack);
}

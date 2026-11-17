/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_pop_top.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 03:42:28 by eallam            #+#    #+#             */
/*   Updated: 2026/11/11 05:14:33 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_stack_status	stack_pop_top(t_stack *stack, int *popped_value)
{
	if (stack->size == 0)
		return (STACK_UNCHANGED);
	*popped_value = stack->data[stack->head];
	++stack->head;
	if (stack->head == stack->capacity)
		stack->head = 0;
	--stack->size;
	return (STACK_CHANGED);
}

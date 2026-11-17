/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 03:42:28 by eallam            #+#    #+#             */
/*   Updated: 2026/11/11 05:14:39 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_stack_status	stack_rotate(t_stack *stack)
{
	int		top_value;
	size_t	bottom_index;

	if (stack->size < 2)
		return (STACK_UNCHANGED);
	top_value = stack->data[stack->head];
	++stack->head;
	if (stack->head == stack->capacity)
		stack->head = 0;
	bottom_index = (stack->head + stack->size - 1) % stack->capacity;
	stack->data[bottom_index] = top_value;
	return (STACK_CHANGED);
}

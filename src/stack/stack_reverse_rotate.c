/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_reverse_rotate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 03:42:28 by eallam            #+#    #+#             */
/*   Updated: 2026/11/11 05:14:37 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_stack_status	stack_reverse_rotate(t_stack *stack)
{
	int		bottom_value;
	size_t	bottom_index;

	if (stack->size < 2)
		return (STACK_UNCHANGED);
	bottom_index = (stack->head + stack->size - 1) % stack->capacity;
	bottom_value = stack->data[bottom_index];
	if (stack->head == 0)
		stack->head = stack->capacity - 1;
	else
		--stack->head;
	stack->data[stack->head] = bottom_value;
	return (STACK_CHANGED);
}

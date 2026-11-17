/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push_top.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 03:42:28 by eallam            #+#    #+#             */
/*   Updated: 2026/11/11 05:14:35 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_stack_status	stack_push_top(t_stack *stack, int new_value)
{
	if (stack->size == stack->capacity)
		return (STACK_UNCHANGED);
	if (stack->head == 0)
		stack->head = stack->capacity - 1;
	else
		--stack->head;
	stack->data[stack->head] = new_value;
	++stack->size;
	return (STACK_CHANGED);
}

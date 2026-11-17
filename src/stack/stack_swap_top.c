/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_swap_top.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 03:42:28 by eallam            #+#    #+#             */
/*   Updated: 2026/11/11 05:14:41 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_stack_status	stack_swap_top(t_stack *stack)
{
	size_t	second;
	int		temp;

	if (stack->size < 2)
		return (STACK_UNCHANGED);
	second = stack->head + 1;
	if (second == stack->capacity)
		second = 0;
	temp = stack->data[stack->head];
	stack->data[stack->head] = stack->data[second];
	stack->data[second] = temp;
	return (STACK_CHANGED);
}

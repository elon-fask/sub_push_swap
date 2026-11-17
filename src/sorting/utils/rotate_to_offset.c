/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_to_offset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "sorting_utils.h"

static void	rotate_once(t_context *context, t_stack *stack, bool reverse)
{
	if (stack == &context->stacks.a)
	{
		if (reverse)
			operation_rra(stack, &context->stats);
		else
			operation_ra(stack, &context->stats);
	}
	else if (reverse)
		operation_rrb(stack, &context->stats);
	else
		operation_rb(stack, &context->stats);
}

static void	rotate_steps(t_context *context, t_stack *stack, size_t steps,
		bool reverse)
{
	while (steps > 0)
	{
		rotate_once(context, stack, reverse);
		--steps;
	}
}

void	sorting_rotate_to_offset(t_context *context, t_stack *stack,
		size_t target_offset, bool forward_on_tie)
{
	size_t	forward_steps;
	size_t	reverse_steps;

	forward_steps = sorting_rotation_distance(stack->size, target_offset,
			false);
	reverse_steps = sorting_rotation_distance(stack->size, target_offset,
			true);
	if (forward_steps < reverse_steps
		|| (forward_on_tie && forward_steps == reverse_steps))
		rotate_steps(context, stack, forward_steps, false);
	else
		rotate_steps(context, stack, reverse_steps, true);
}

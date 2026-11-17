/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_cost_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "turk_internal.h"

void	turk_calculate_rotation_cost(t_turk_move *move)
{
	if (move->source_reverse != move->target_reverse)
		move->total_cost = move->source_rotations + move->target_rotations;
	else if (move->source_rotations > move->target_rotations)
		move->total_cost = move->source_rotations;
	else
		move->total_cost = move->target_rotations;
}

void	turk_rotate_source(t_context *context, const t_turk_move *move)
{
	if (move->source_is_a && move->source_reverse)
		operation_rra(&context->stacks.a, &context->stats);
	else if (move->source_is_a)
		operation_ra(&context->stacks.a, &context->stats);
	else if (move->source_reverse)
		operation_rrb(&context->stacks.b, &context->stats);
	else
		operation_rb(&context->stacks.b, &context->stats);
}

void	turk_rotate_target(t_context *context, const t_turk_move *move)
{
	if (move->source_is_a && move->target_reverse)
		operation_rrb(&context->stacks.b, &context->stats);
	else if (move->source_is_a)
		operation_rb(&context->stacks.b, &context->stats);
	else if (move->target_reverse)
		operation_rra(&context->stacks.a, &context->stats);
	else
		operation_ra(&context->stacks.a, &context->stats);
}

void	turk_rotate_both(t_context *context, bool reverse)
{
	if (reverse)
		operation_rrr(&context->stacks, &context->stats);
	else
		operation_rr(&context->stacks, &context->stats);
}

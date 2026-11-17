/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "turk_internal.h"

static void	rotate_shared(t_context *context, const t_turk_move *move,
		size_t *source_rotations, size_t *target_rotations)
{
	while (*source_rotations > 0 && *target_rotations > 0
		&& move->source_reverse == move->target_reverse)
	{
		turk_rotate_both(context, move->source_reverse);
		--*source_rotations;
		--*target_rotations;
	}
}

static void	rotate_remaining_source(t_context *context,
		const t_turk_move *move, size_t rotations)
{
	while (rotations > 0)
	{
		turk_rotate_source(context, move);
		--rotations;
	}
}

static void	rotate_remaining_target(t_context *context,
		const t_turk_move *move, size_t rotations)
{
	while (rotations > 0)
	{
		turk_rotate_target(context, move);
		--rotations;
	}
}

static void	push_move(t_context *context, const t_turk_move *move)
{
	if (move->source_is_a)
		operation_pb(&context->stacks, &context->stats);
	else
		operation_pa(&context->stacks, &context->stats);
}

void	turk_execute_move(t_context *context, const t_turk_move *move)
{
	size_t	source_rotations;
	size_t	target_rotations;

	source_rotations = move->source_rotations;
	target_rotations = move->target_rotations;
	rotate_shared(context, move, &source_rotations, &target_rotations);
	rotate_remaining_source(context, move, source_rotations);
	rotate_remaining_target(context, move, target_rotations);
	push_move(context, move);
}

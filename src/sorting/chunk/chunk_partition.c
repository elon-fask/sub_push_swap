/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_partition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chunk_internal.h"
#include "operations.h"
#include "sorting_utils.h"

void	chunk_calculate_width(size_t *width, size_t size)
{
	size_t	root;

	root = 1;
	while (root <= size / root)
		++root;
	*width = (root - 1) * 2;
}

void	chunk_process_range(t_chunk_state *state)
{
	t_context	*context;
	size_t		remaining;
	int			rank;

	context = state->context;
	remaining = state->end - state->start;
	while (remaining > 0)
	{
		rank = sorting_value_at(&context->stacks.a, 0);
		if ((size_t)rank >= state->start && (size_t)rank < state->end)
		{
			operation_pb(&context->stacks, &context->stats);
			if ((size_t)rank < state->start
				+ (state->end - state->start) / 2)
				operation_rb(&context->stacks.b, &context->stats);
			--remaining;
		}
		else
			operation_ra(&context->stacks.a, &context->stats);
	}
}

void	chunk_partition(t_chunk_state *state)
{
	state->start = 0;
	while (state->start < state->size)
	{
		if (state->width > state->size - state->start)
			state->end = state->size;
		else
			state->end = state->start + state->width;
		chunk_process_range(state);
		state->start = state->end;
	}
}

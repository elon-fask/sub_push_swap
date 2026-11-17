/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_restore.c                                    :+:      :+:    :+:   */
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

void	chunk_push_back(t_chunk_state *state)
{
	t_context	*context;
	size_t		maximum_offset;

	context = state->context;
	while (context->stacks.b.size > 0)
	{
		maximum_offset = sorting_maximum_offset(&context->stacks.b);
		sorting_rotate_to_offset(context, &context->stacks.b,
			maximum_offset, false);
		operation_pa(&context->stacks, &context->stats);
	}
}

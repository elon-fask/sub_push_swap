/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_five.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "small_sort_internal.h"
#include "sorting_utils.h"

static void	move_minimum_to_b(t_context *context)
{
	size_t	minimum_offset;

	minimum_offset = sorting_minimum_offset(&context->stacks.a);
	sorting_rotate_to_offset(context, &context->stacks.a,
		minimum_offset, false);
	operation_pb(&context->stacks, &context->stats);
}

void	sort_five(t_context *context)
{
	while (context->stacks.a.size > 3)
		move_minimum_to_b(context);
	sort_three(context);
	while (context->stacks.b.size > 0)
		operation_pa(&context->stacks, &context->stats);
}

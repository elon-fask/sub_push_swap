/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
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

void	sort_three(t_context *context)
{
	size_t	maximum_offset;
	t_stack	*stack;

	stack = &context->stacks.a;
	maximum_offset = sorting_maximum_offset(stack);
	if (maximum_offset == 0)
		operation_ra(stack, &context->stats);
	else if (maximum_offset == 1)
		operation_rra(stack, &context->stats);
	if (sorting_value_at(stack, 0) > sorting_value_at(stack, 1))
		operation_sa(stack, &context->stats);
}

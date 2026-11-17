/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_lookup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sorting_utils.h"

size_t	sorting_index_at(const t_stack *stack, size_t offset)
{
	return ((stack->head + offset) % stack->capacity);
}

int	sorting_value_at(const t_stack *stack, size_t offset)
{
	return (stack->data[sorting_index_at(stack, offset)]);
}

static size_t	find_extreme_offset(const t_stack *stack, bool minimum)
{
	size_t	i;
	size_t	best_offset;
	int		best;
	int		current;

	best_offset = 0;
	best = sorting_value_at(stack, 0);
	i = 1;
	while (i < stack->size)
	{
		current = sorting_value_at(stack, i);
		if ((minimum && current < best) || (!minimum && current > best))
		{
			best = current;
			best_offset = i;
		}
		++i;
	}
	return (best_offset);
}

size_t	sorting_minimum_offset(const t_stack *stack)
{
	return (find_extreme_offset(stack, true));
}

size_t	sorting_maximum_offset(const t_stack *stack)
{
	return (find_extreme_offset(stack, false));
}

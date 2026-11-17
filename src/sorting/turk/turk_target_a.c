/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_target_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "turk_internal.h"
#include "sorting_utils.h"

static bool	find_successor(const t_stack *stack, int value, size_t *target)
{
	bool	found;
	int		best;
	int		current;
	size_t	i;

	found = false;
	i = 0;
	while (i < stack->size)
	{
		current = sorting_value_at(stack, i);
		if (current > value && (!found || current < best))
		{
			best = current;
			*target = i;
			found = true;
		}
		++i;
	}
	return (found);
}

void	turk_target_in_a(size_t *target, int value, const t_stack *a)
{
	if (!find_successor(a, value, target))
		*target = sorting_minimum_offset(a);
}

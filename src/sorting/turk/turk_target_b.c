/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_target_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "turk_internal.h"
#include "sorting_utils.h"

static bool	find_predecessor(const t_stack *stack, int value, size_t *target)
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
		if (current < value && (!found || current > best))
		{
			best = current;
			*target = i;
			found = true;
		}
		++i;
	}
	return (found);
}

void	turk_target_in_b(size_t *target, int value, const t_stack *b)
{
	if (b->size == 0)
	{
		*target = 0;
		return ;
	}
	if (!find_predecessor(b, value, target))
		*target = sorting_maximum_offset(b);
}

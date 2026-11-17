/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "turk_internal.h"
#include "sorting_utils.h"

static t_turk_move	make_candidate(const t_stack *source,
		const t_stack *destination, size_t index, bool source_is_a)
{
	t_turk_move	candidate;
	int			value;

	value = sorting_value_at(source, index);
	candidate = (t_turk_move){0};
	candidate.source_index = index;
	if (source_is_a)
		turk_target_in_b(&candidate.target_index, value, destination);
	else
		turk_target_in_a(&candidate.target_index, value, destination);
	candidate.source_is_a = source_is_a;
	return (candidate);
}

static void	consider_direction(t_turk_move_search *search,
		const t_turk_move *base, bool source_reverse, bool target_reverse)
{
	t_turk_move	candidate;

	candidate = *base;
	candidate.source_reverse = source_reverse;
	candidate.target_reverse = target_reverse;
	candidate.source_rotations = sorting_rotation_distance(
			search->source_size, base->source_index, source_reverse);
	candidate.target_rotations = sorting_rotation_distance(
			search->target_size, base->target_index, target_reverse);
	turk_calculate_rotation_cost(&candidate);
	if (!search->has_best || candidate.total_cost < search->best.total_cost)
	{
		search->best = candidate;
		search->has_best = true;
	}
}

static void	consider_directions(t_turk_move_search *search,
		const t_turk_move *candidate)
{
	int	source_direction;
	int	target_direction;

	source_direction = 0;
	while (source_direction < 2)
	{
		target_direction = 0;
		while (target_direction < 2)
		{
			consider_direction(search, candidate, source_direction == 1,
				target_direction == 1);
			++target_direction;
		}
		++source_direction;
	}
}

void	turk_find_cheapest_move(t_turk_move *move, const t_stack *source,
		const t_stack *destination, bool source_is_a)
{
	t_turk_move_search	search;
	t_turk_move			candidate;
	size_t				i;

	search = (t_turk_move_search){0};
	search.source_size = source->size;
	search.target_size = destination->size;
	i = 0;
	while (i < source->size)
	{
		candidate = make_candidate(source, destination, i, source_is_a);
		consider_directions(&search, &candidate);
		++i;
	}
	*move = search.best;
}

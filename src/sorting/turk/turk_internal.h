/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TURK_INTERNAL_H
# define TURK_INTERNAL_H

# include <stdbool.h>
# include <stddef.h>
# include "turk.h"

typedef struct s_turk_move
{
	size_t	source_index;
	size_t	target_index;
	size_t	source_rotations;
	size_t	target_rotations;
	size_t	total_cost;
	bool	source_is_a;
	bool	source_reverse;
	bool	target_reverse;
}				t_turk_move;

typedef struct s_turk_move_search
{
	t_turk_move	best;
	size_t		source_size;
	size_t		target_size;
	bool		has_best;
}			t_turk_move_search;

void		turk_target_in_a(size_t *target, int value,
				const t_stack *a);
void		turk_target_in_b(size_t *target, int value,
				const t_stack *b);

void		turk_find_cheapest_move(t_turk_move *move,
				const t_stack *source, const t_stack *destination,
				bool source_is_a);
void		turk_calculate_rotation_cost(t_turk_move *move);

void		turk_execute_move(t_context *context, const t_turk_move *move);
void		turk_rotate_source(t_context *context, const t_turk_move *move);
void		turk_rotate_target(t_context *context, const t_turk_move *move);
void		turk_rotate_both(t_context *context, bool reverse);
void		turk_sort_small(t_context *context);
void		turk_rotate_minimum_to_top(t_context *context);

#endif /* TURK_INTERNAL_H */

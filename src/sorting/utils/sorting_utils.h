/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORTING_UTILS_H
# define SORTING_UTILS_H

# include <stdbool.h>
# include <stddef.h>
# include "push_swap_internal.h"

size_t	sorting_index_at(const t_stack *stack, size_t offset);
int		sorting_value_at(const t_stack *stack, size_t offset);
size_t	sorting_minimum_offset(const t_stack *stack);
size_t	sorting_maximum_offset(const t_stack *stack);
size_t	sorting_rotation_distance(size_t size, size_t offset,
			bool reverse);

void	sorting_rotate_to_offset(t_context *context, t_stack *stack,
			size_t target_offset, bool forward_on_tie);

#endif /* SORTING_UTILS_H */

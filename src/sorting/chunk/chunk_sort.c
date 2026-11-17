/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/16 15:51:18 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chunk_internal.h"
#include "libft.h"
#include "small_sort.h"
#include "turk.h"
#include <stdlib.h>

void	chunk_sort(t_context *context)
{
	t_chunk_state	state;

	if (context->stacks.a.size <= 5)
	{
		small_sort(context);
		return ;
	}
	state = (t_chunk_state){0};
	state.context = context;
	state.size = context->stacks.a.size;
	state.items = ft_calloc(state.size, sizeof(*state.items));
	if (state.items == NULL)
	{
		stats_set_selected_strategy(&context->stats, STRATEGY_COMPLEX);
		turk_sort(context);
		return ;
	}
	chunk_calculate_width(&state.width, state.size);
	chunk_rank_values(&state);
	chunk_partition(&state);
	chunk_push_back(&state);
	chunk_restore_values(&state);
	free(state.items);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chunk_internal.h"
#include "sorting_utils.h"
#include <stddef.h>

static void	swap_chunk_items(t_chunk_item *left, t_chunk_item *right)
{
	t_chunk_item	temp;

	temp = *left;
	*left = *right;
	*right = temp;
}

static void	sift_chunk_heap(t_chunk_item *items, size_t size, size_t root)
{
	size_t	child;

	while (root < size / 2)
	{
		child = root * 2 + 1;
		if (child + 1 < size
			&& items[child].value < items[child + 1].value)
			++child;
		if (items[root].value >= items[child].value)
			return ;
		swap_chunk_items(&items[root], &items[child]);
		root = child;
	}
}

static void	sort_chunk_items(t_chunk_item *items, size_t size)
{
	size_t	start;
	size_t	end;

	start = size / 2;
	while (start > 0)
		sift_chunk_heap(items, size, --start);
	end = size;
	while (end > 1)
	{
		--end;
		swap_chunk_items(&items[0], &items[end]);
		sift_chunk_heap(items, end, 0);
	}
}

void	chunk_rank_values(t_chunk_state *state)
{
	t_stack	*a;
	size_t	i;

	a = &state->context->stacks.a;
	i = 0;
	while (i < state->size)
	{
		state->items[i].value = sorting_value_at(a, i);
		state->items[i].physical_index = sorting_index_at(a, i);
		++i;
	}
	sort_chunk_items(state->items, state->size);
	i = 0;
	while (i < state->size)
	{
		a->data[state->items[i].physical_index] = (int)i;
		++i;
	}
}

void	chunk_restore_values(t_chunk_state *state)
{
	t_stack	*a;
	size_t	i;
	size_t	physical_index;
	size_t	rank;

	a = &state->context->stacks.a;
	i = 0;
	while (i < a->size)
	{
		physical_index = sorting_index_at(a, i);
		rank = (size_t)a->data[physical_index];
		a->data[physical_index] = state->items[rank].value;
		++i;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 18:42:13 by eallam            #+#    #+#             */
/*   Updated: 2026/11/12 20:50:46 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_internal.h"
#include "libft.h"
#include <stdint.h>
#include <stdlib.h>

static size_t	calculate_capacity(size_t capacity, size_t required_capacity)
{
	if (capacity == 0)
		capacity = LIBFT_GET_NEXT_LINE_BUFFER_SIZE * 2;
	while (capacity < required_capacity)
	{
		if (capacity >= SIZE_MAX / 2)
			return (0);
		capacity *= 2;
	}
	return (capacity);
}

static bool	grow_buffer(t_gnl_state *state, size_t required_capacity)
{
	char	*new_data;
	size_t	new_capacity;
	size_t	unread_bytes;

	new_capacity = calculate_capacity(state->capacity, required_capacity);
	if (new_capacity == 0)
		return (false);
	new_data = malloc(new_capacity);
	if (!new_data)
		return (false);
	unread_bytes = state->data_end - state->read_pos;
	if (unread_bytes > 0)
		ft_memcpy(new_data, state->data + state->read_pos, unread_bytes);
	free(state->data);
	state->data = new_data;
	state->capacity = new_capacity;
	state->scan_pos -= state->read_pos;
	state->read_pos = 0;
	state->data_end = unread_bytes;
	return (true);
}

static void	compact_buffer(t_gnl_state *state)
{
	size_t	remaining_bytes;

	if (state->read_pos == state->data_end)
	{
		state->read_pos = 0;
		state->scan_pos = 0;
		state->data_end = 0;
		return ;
	}
	remaining_bytes = state->data_end - state->read_pos;
	ft_memmove(state->data, state->data + state->read_pos, remaining_bytes);
	state->scan_pos -= state->read_pos;
	state->read_pos = 0;
	state->data_end = remaining_bytes;
}

bool	ensure_buffer_space(t_gnl_state *state, size_t incoming_bytes)
{
	size_t	tail_space;
	size_t	unread_bytes;
	size_t	required_capacity;

	tail_space = state->capacity - state->data_end;
	if (tail_space >= incoming_bytes)
		return (true);
	unread_bytes = state->data_end - state->read_pos;
	if (state->capacity - unread_bytes >= incoming_bytes)
	{
		compact_buffer(state);
		return (true);
	}
	if (incoming_bytes > SIZE_MAX - unread_bytes)
		return (false);
	required_capacity = unread_bytes + incoming_bytes;
	return (grow_buffer(state, required_capacity));
}

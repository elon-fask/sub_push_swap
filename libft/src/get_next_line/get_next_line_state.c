/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_internal.h"
#include <stdlib.h>

t_gnl_state	*get_next_line_state(void)
{
	static t_gnl_state	state;

	return (&state);
}

void	reset_gnl_state(t_gnl_state *state)
{
	free(state->data);
	state->data = NULL;
	state->capacity = 0;
	state->read_pos = 0;
	state->scan_pos = 0;
	state->data_end = 0;
	state->eof = false;
	state->failed = false;
}

void	get_next_line_cleanup(void)
{
	reset_gnl_state(get_next_line_state());
}

bool	get_next_line_has_error(void)
{
	return (get_next_line_state()->failed);
}

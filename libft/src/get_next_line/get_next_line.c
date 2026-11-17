/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 18:42:04 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_internal.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static t_gnl_status	save_line(t_gnl_state *state, char **line,
		size_t line_end)
{
	size_t	line_length;

	line_length = line_end - state->read_pos;
	*line = malloc(line_length + 1);
	if (*line == NULL)
		return (GNL_ERROR);
	ft_memcpy(*line, state->data + state->read_pos, line_length);
	(*line)[line_length] = '\0';
	state->read_pos = line_end;
	state->scan_pos = line_end;
	return (GNL_LINE_READY);
}

static t_gnl_status	extract_line(t_gnl_state *state, char **line)
{
	while (state->scan_pos < state->data_end)
	{
		if (state->data[state->scan_pos] == '\n')
			return (save_line(state, line, state->scan_pos + 1));
		++state->scan_pos;
	}
	if (!state->eof || state->read_pos == state->data_end)
		return (GNL_NEED_INPUT);
	return (save_line(state, line, state->data_end));
}

static bool	fill_buffer(int fd, t_gnl_state *state)
{
	ssize_t	bytes_read;

	if (!ensure_buffer_space(state, LIBFT_GET_NEXT_LINE_BUFFER_SIZE))
		return (false);
	bytes_read = read(fd, state->data + state->data_end,
			LIBFT_GET_NEXT_LINE_BUFFER_SIZE);
	if (bytes_read < 0)
		return (false);
	if (bytes_read == 0)
		state->eof = true;
	else
		state->data_end += (size_t)bytes_read;
	return (true);
}

static char	*fail_gnl_state(t_gnl_state *state)
{
	reset_gnl_state(state);
	state->failed = true;
	return (NULL);
}

char	*get_next_line(int fd)
{
	t_gnl_state		*state;
	char			*line;
	t_gnl_status	status;

	state = get_next_line_state();
	state->failed = false;
	if (fd < 0)
		return (fail_gnl_state(state));
	while (true)
	{
		status = extract_line(state, &line);
		if (status == GNL_LINE_READY)
			return (line);
		if (status == GNL_ERROR)
			return (fail_gnl_state(state));
		if (state->eof)
		{
			reset_gnl_state(state);
			return (NULL);
		}
		if (!fill_buffer(fd, state))
			return (fail_gnl_state(state));
	}
}

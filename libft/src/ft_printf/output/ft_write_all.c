/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:52:54 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 02:59:47 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include <limits.h>
#include <unistd.h>

static size_t	ft_get_write_chunk(size_t remaining)
{
	if (remaining > (size_t)SSIZE_MAX)
		return ((size_t)SSIZE_MAX);
	return (remaining);
}

int	ft_write_all(int fd, const void *buffer, size_t length)
{
	const unsigned char	*cursor;
	size_t				remaining;
	ssize_t				written;

	if (length == 0)
		return (0);
	if (!buffer)
		return (-1);
	cursor = buffer;
	remaining = length;
	while (remaining > 0)
	{
		written = write(fd, cursor, ft_get_write_chunk(remaining));
		if (written <= 0)
			return (-1);
		cursor += (size_t)written;
		remaining -= (size_t)written;
	}
	return (0);
}

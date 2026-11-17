/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_repeat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:52:51 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 03:00:06 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

#define FT_OUTPUT_BUFFER_SIZE 4096

static int	ft_write_repeated(t_output *out, const char *buffer, size_t chunk,
		size_t count)
{
	while (count > 0)
	{
		if (count < chunk)
			chunk = count;
		if (ft_output_write(out, buffer, chunk) < 0)
			return (-1);
		count -= chunk;
	}
	return (0);
}

int	ft_output_repeat(t_output *out, char c, size_t count)
{
	char	buffer[FT_OUTPUT_BUFFER_SIZE];
	size_t	chunk;

	if (out->failed)
		return (-1);
	if (count == 0)
		return (0);
	if (count > SIZE_MAX - out->count)
	{
		out->failed = true;
		return (-1);
	}
	chunk = count;
	if (chunk > sizeof(buffer))
		chunk = sizeof(buffer);
	ft_memset(buffer, (unsigned char)c, chunk);
	return (ft_write_repeated(out, buffer, chunk, count));
}

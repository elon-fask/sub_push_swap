/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:53:18 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 03:22:15 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

static int	ft_validate_base(unsigned int base, const char *alphabet)
{
	if (base < 2 || !alphabet)
		return (-1);
	if (ft_strlen(alphabet) < base)
		return (-1);
	return (0);
}

static int	ft_store_digit(t_digit_buffer *buffer, char **cursor, char digit)
{
	if (*cursor == buffer->data)
	{
		buffer->length = 0;
		return (-1);
	}
	*(--(*cursor)) = digit;
	buffer->length++;
	return (0);
}

int	ft_utoa_base(uintmax_t value, unsigned int base, const char *alphabet,
		t_digit_buffer *buffer)
{
	char	*cursor;

	if (!buffer || !buffer->data)
		return (-1);
	buffer->length = 0;
	if (buffer->capacity < 2 || ft_validate_base(base, alphabet) < 0)
		return (-1);
	cursor = buffer->data + buffer->capacity;
	*--cursor = '\0';
	if (value == 0)
		return (ft_store_digit(buffer, &cursor, alphabet[0]));
	while (value > 0)
	{
		if (ft_store_digit(buffer, &cursor, alphabet[value % base]) < 0)
			return (-1);
		value /= base;
	}
	return (0);
}

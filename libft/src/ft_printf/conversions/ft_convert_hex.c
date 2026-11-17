/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:52:16 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 04:23:18 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include <limits.h>

static const char	*ft_get_hex_alphabet(char specifier)
{
	if (specifier == 'x')
		return ("0123456789abcdef");
	return ("0123456789ABCDEF");
}

static const char	*ft_get_hex_prefix(const t_format_spec *spec,
		unsigned int value)
{
	if (!spec->flags.alternate || value == 0)
		return (NULL);
	if (spec->specifier == 'x')
		return ("0x");
	return ("0X");
}

int	ft_convert_hex(t_context *ctx, const t_format_spec *spec)
{
	t_integer_repr	repr;
	char			digits[sizeof(uintmax_t) * CHAR_BIT + 1];
	t_digit_buffer	buffer;
	unsigned int	value;

	value = va_arg(ctx->args, unsigned int);
	buffer.data = digits;
	buffer.capacity = sizeof(digits);
	if (ft_utoa_base(value, 16, ft_get_hex_alphabet(spec->specifier),
			&buffer) < 0)
		return (-1);
	repr.digits = buffer.data + buffer.capacity - 1 - buffer.length;
	repr.digits_len = buffer.length;
	repr.sign = '\0';
	repr.prefix = ft_get_hex_prefix(spec, value);
	repr.prefix_len = 0;
	if (repr.prefix != NULL)
		repr.prefix_len = 2;
	return (ft_emit_integer_field(&ctx->output, spec, &repr));
}

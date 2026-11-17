/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_octal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 16:40:52 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 04:23:23 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include <limits.h>

static const char	*ft_get_octal_prefix(const t_format_spec *spec,
		unsigned int value, size_t digits_len)
{
	if (!spec->flags.alternate)
		return (NULL);
	if (value == 0)
	{
		if (spec->has_precision && spec->precision == 0)
			return ("0");
		return (NULL);
	}
	if (spec->has_precision && spec->precision > digits_len)
		return (NULL);
	return ("0");
}

int	ft_convert_octal(t_context *ctx, const t_format_spec *spec)
{
	t_integer_repr	repr;
	char			digits[sizeof(uintmax_t) * CHAR_BIT + 1];
	t_digit_buffer	buffer;
	unsigned int	value;

	value = va_arg(ctx->args, unsigned int);
	buffer.data = digits;
	buffer.capacity = sizeof(digits);
	if (ft_utoa_base(value, 8, "01234567", &buffer) < 0)
		return (-1);
	repr.digits = buffer.data + buffer.capacity - 1 - buffer.length;
	repr.digits_len = buffer.length;
	repr.sign = '\0';
	repr.prefix = ft_get_octal_prefix(spec, value, buffer.length);
	repr.prefix_len = 0;
	if (repr.prefix != NULL)
		repr.prefix_len = 1;
	return (ft_emit_integer_field(&ctx->output, spec, &repr));
}

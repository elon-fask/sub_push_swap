/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_unsigned.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:52:26 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 04:23:42 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include <limits.h>

int	ft_convert_unsigned(t_context *ctx, const t_format_spec *spec)
{
	t_integer_repr	repr;
	char			digits[sizeof(uintmax_t) * CHAR_BIT + 1];
	t_digit_buffer	buffer;
	unsigned int	value;

	value = va_arg(ctx->args, unsigned int);
	buffer.data = digits;
	buffer.capacity = sizeof(digits);
	if (ft_utoa_base(value, 10, "0123456789", &buffer) < 0)
		return (-1);
	repr.digits = buffer.data + buffer.capacity - 1 - buffer.length;
	repr.digits_len = buffer.length;
	repr.sign = '\0';
	repr.prefix = NULL;
	repr.prefix_len = 0;
	return (ft_emit_integer_field(&ctx->output, spec, &repr));
}

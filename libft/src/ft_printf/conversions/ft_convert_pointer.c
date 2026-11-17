/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:52:21 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 04:23:31 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include <limits.h>

static int	ft_emit_null_pointer(t_context *ctx, const t_format_spec *spec)
{
	t_text_repr	repr;

	repr.data = "(nil)";
	repr.length = 5;
	return (ft_emit_text_field(&ctx->output, spec, &repr));
}

int	ft_convert_pointer(t_context *ctx, const t_format_spec *spec)
{
	t_integer_repr	repr;
	char			digits[sizeof(uintmax_t) * CHAR_BIT + 1];
	t_digit_buffer	buffer;
	void			*argument;
	uintptr_t		value;

	argument = va_arg(ctx->args, void *);
	if (argument == NULL)
		return (ft_emit_null_pointer(ctx, spec));
	buffer.data = digits;
	buffer.capacity = sizeof(digits);
	value = (uintptr_t)argument;
	if (ft_utoa_base((uintmax_t)value, 16, "0123456789abcdef", &buffer) < 0)
		return (-1);
	repr.digits = buffer.data + buffer.capacity - 1 - buffer.length;
	repr.digits_len = buffer.length;
	repr.sign = '\0';
	repr.prefix = "0x";
	repr.prefix_len = 2;
	return (ft_emit_integer_field(&ctx->output, spec, &repr));
}

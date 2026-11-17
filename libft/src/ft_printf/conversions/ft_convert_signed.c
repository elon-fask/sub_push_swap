/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_signed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 04:26:02 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 04:26:03 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include <limits.h>

static void	ft_set_signed_sign(t_integer_repr *repr, int value,
		const t_format_spec *spec)
{
	if (value < 0)
		repr->sign = '-';
	else if (spec->flags.plus)
		repr->sign = '+';
	else if (spec->flags.space)
		repr->sign = ' ';
	else
		repr->sign = '\0';
}

int	ft_convert_signed(t_context *ctx, const t_format_spec *spec)
{
	t_integer_repr	repr;
	char			digits[sizeof(uintmax_t) * CHAR_BIT + 1];
	t_digit_buffer	buffer;
	int				value;
	unsigned int	magnitude;

	value = va_arg(ctx->args, int);
	magnitude = (unsigned int)value;
	if (value < 0)
		magnitude = 0U - magnitude;
	ft_set_signed_sign(&repr, value, spec);
	buffer.data = digits;
	buffer.capacity = sizeof(digits);
	if (ft_utoa_base(magnitude, 10, "0123456789", &buffer) < 0)
		return (-1);
	repr.digits = buffer.data + buffer.capacity - 1 - buffer.length;
	repr.digits_len = buffer.length;
	repr.prefix = NULL;
	repr.prefix_len = 0;
	return (ft_emit_integer_field(&ctx->output, spec, &repr));
}

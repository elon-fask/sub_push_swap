/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_emit_integer_field.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 04:17:22 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 04:17:25 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static size_t	ft_get_digits_len(const t_format_spec *spec,
		const t_integer_repr *repr)
{
	if (spec->has_precision && spec->precision == 0 && repr->digits_len == 1
		&& repr->digits[0] == '0')
		return (0);
	return (repr->digits_len);
}

static int	ft_emit_leading(t_output *out, const t_format_spec *spec,
		const t_integer_repr *repr, size_t padding)
{
	if (!spec->flags.left && (spec->has_precision || !spec->flags.zero)
		&& ft_output_repeat(out, ' ', padding) < 0)
		return (-1);
	if (repr->sign != '\0' && ft_output_write(out, &repr->sign, 1) < 0)
		return (-1);
	if (repr->prefix_len > 0 && ft_output_write(out, repr->prefix,
			repr->prefix_len) < 0)
		return (-1);
	if (!spec->flags.left && !spec->has_precision && spec->flags.zero
		&& ft_output_repeat(out, '0', padding) < 0)
		return (-1);
	return (0);
}

static int	ft_emit_digits(t_output *out, const t_integer_repr *repr,
		size_t digits_len, size_t precision_zeroes)
{
	if (ft_output_repeat(out, '0', precision_zeroes) < 0)
		return (-1);
	return (ft_output_write(out, repr->digits, digits_len));
}

int	ft_emit_integer_field(t_output *out, const t_format_spec *spec,
		const t_integer_repr *repr)
{
	size_t	digits_len;
	size_t	precision_zeroes;
	size_t	total;
	size_t	padding;

	digits_len = ft_get_digits_len(spec, repr);
	precision_zeroes = 0;
	if (spec->has_precision && spec->precision > digits_len)
		precision_zeroes = spec->precision - digits_len;
	total = repr->prefix_len + precision_zeroes + digits_len;
	if (repr->sign != '\0')
		total++;
	padding = 0;
	if (spec->width > total)
		padding = spec->width - total;
	if (ft_emit_leading(out, spec, repr, padding) < 0)
		return (-1);
	if (ft_emit_digits(out, repr, digits_len, precision_zeroes) < 0)
		return (-1);
	if (spec->flags.left)
		return (ft_output_repeat(out, ' ', padding));
	return (0);
}

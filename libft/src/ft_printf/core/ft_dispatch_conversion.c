/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch_conversion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 02:15:40 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 02:15:42 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int	ft_dispatch_conversion(t_context *ctx, const t_format_spec *spec)
{
	if (spec->specifier == 'c')
		return (ft_convert_char(ctx, spec));
	if (spec->specifier == 's')
		return (ft_convert_string(ctx, spec));
	if (spec->specifier == 'p')
		return (ft_convert_pointer(ctx, spec));
	if (spec->specifier == 'd' || spec->specifier == 'i')
		return (ft_convert_signed(ctx, spec));
	if (spec->specifier == 'u')
		return (ft_convert_unsigned(ctx, spec));
	if (spec->specifier == 'o')
		return (ft_convert_octal(ctx, spec));
	if (spec->specifier == 'x' || spec->specifier == 'X')
		return (ft_convert_hex(ctx, spec));
	if (spec->specifier == 'b' || spec->specifier == 'B')
		return (ft_convert_binary(ctx, spec));
	if (spec->specifier == '%')
		return (ft_convert_percent(ctx, spec));
	return (-1);
}

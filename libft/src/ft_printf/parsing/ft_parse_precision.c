/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_precision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:53:04 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 02:21:23 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static void	ft_parse_dynamic_precision(t_context *ctx, t_format_spec *spec)
{
	int	precision;

	precision = va_arg(ctx->args, int);
	if (precision < 0)
	{
		spec->has_precision = false;
		spec->precision = 0;
	}
	else
		spec->precision = (size_t)precision;
	ctx->cursor++;
}

int	ft_parse_precision(t_context *ctx, t_format_spec *spec)
{
	if (*ctx->cursor != '.')
		return (0);
	ctx->cursor++;
	spec->has_precision = true;
	spec->precision = 0;
	if (*ctx->cursor == '*')
	{
		ft_parse_dynamic_precision(ctx, spec);
		return (0);
	}
	if (*ctx->cursor < '0' || *ctx->cursor > '9')
		return (0);
	return (ft_parse_decimal(ctx, &spec->precision));
}

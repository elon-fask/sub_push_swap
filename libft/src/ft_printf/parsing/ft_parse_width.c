/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:53:07 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 02:19:44 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static void	ft_parse_dynamic_width(t_context *ctx, t_format_spec *spec)
{
	int	width;

	width = va_arg(ctx->args, int);
	if (width < 0)
	{
		spec->flags.left = 1;
		spec->width = (size_t)(-(width + 1)) + 1;
	}
	else
		spec->width = (size_t)width;
	ctx->cursor++;
}

int	ft_parse_width(t_context *ctx, t_format_spec *spec)
{
	if (*ctx->cursor == '*')
	{
		ft_parse_dynamic_width(ctx, spec);
		return (0);
	}
	if (*ctx->cursor < '0' || *ctx->cursor > '9')
		return (0);
	return (ft_parse_decimal(ctx, &spec->width));
}

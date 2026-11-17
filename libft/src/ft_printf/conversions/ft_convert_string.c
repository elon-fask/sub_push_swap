/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:52:25 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 02:38:20 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

int	ft_convert_string(t_context *ctx, const t_format_spec *spec)
{
	t_text_repr	repr;

	repr.data = va_arg(ctx->args, char *);
	if (!repr.data)
		repr.data = "(null)";
	if (spec->has_precision)
		repr.length = ft_strnlen(repr.data, spec->precision);
	else
		repr.length = ft_strlen(repr.data);
	return (ft_emit_text_field(&ctx->output, spec, &repr));
}

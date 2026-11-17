/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:52:13 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 02:38:09 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int	ft_convert_char(t_context *ctx, const t_format_spec *spec)
{
	t_text_repr		repr;
	unsigned char	character;

	character = (unsigned char)va_arg(ctx->args, int);
	repr.data = (const char *)&character;
	repr.length = 1;
	return (ft_emit_text_field(&ctx->output, spec, &repr));
}

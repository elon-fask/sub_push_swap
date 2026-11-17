/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_emit_literal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:52:33 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 02:12:39 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int	ft_emit_literal(t_context *ctx)
{
	const char	*start;
	size_t		length;

	start = ctx->cursor;
	while (*ctx->cursor && *ctx->cursor != '%')
		ctx->cursor++;
	length = (size_t)(ctx->cursor - start);
	return (ft_output_write(&ctx->output, start, length));
}

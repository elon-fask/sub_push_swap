/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_percent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:52:18 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 02:35:34 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int	ft_convert_percent(t_context *ctx, const t_format_spec *spec)
{
	t_text_repr	repr;

	repr.data = "%";
	repr.length = 1;
	return (ft_emit_text_field(&ctx->output, spec, &repr));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_directive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:53:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 02:14:51 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int	ft_parse_directive(t_context *ctx, t_format_spec *spec)
{
	ctx->cursor++;
	ft_parse_flags(ctx, spec);
	if (ft_parse_width(ctx, spec) < 0)
		return (-1);
	if (ft_parse_precision(ctx, spec) < 0)
		return (-1);
	if (ft_parse_specifier(ctx, spec) < 0)
		return (-1);
	return (0);
}

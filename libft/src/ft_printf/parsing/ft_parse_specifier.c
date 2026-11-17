/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_specifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 02:24:48 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 03:23:27 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

int	ft_parse_specifier(t_context *ctx, t_format_spec *spec)
{
	if (!*ctx->cursor || !ft_strchr("cspdiuxXobB%", *ctx->cursor))
		return (-1);
	spec->specifier = *ctx->cursor;
	ctx->cursor++;
	return (0);
}

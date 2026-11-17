/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:52:39 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 02:11:11 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int	ft_process_format(t_context *ctx)
{
	while (*ctx->cursor)
	{
		if (*ctx->cursor != '%')
		{
			if (ft_emit_literal(ctx) < 0)
				return (-1);
		}
		else if (ft_process_directive(ctx) < 0)
			return (-1);
	}
	return (0);
}

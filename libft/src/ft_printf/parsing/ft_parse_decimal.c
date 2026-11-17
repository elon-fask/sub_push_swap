/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_decimal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:52:58 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 02:17:57 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include <limits.h>

int	ft_parse_decimal(t_context *ctx, size_t *value)
{
	size_t	digit;

	*value = 0;
	while (*ctx->cursor >= '0' && *ctx->cursor <= '9')
	{
		digit = (size_t)(*ctx->cursor - '0');
		if (*value > ((size_t)INT_MAX - digit) / 10)
			return (-1);
		*value = (*value * 10) + digit;
		ctx->cursor++;
	}
	return (0);
}

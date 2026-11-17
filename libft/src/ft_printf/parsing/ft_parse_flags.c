/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 03:36:45 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 03:36:46 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

void	ft_parse_flags(t_context *ctx, t_format_spec *spec)
{
	while (1)
	{
		if (*ctx->cursor == '-')
			spec->flags.left = 1;
		else if (*ctx->cursor == '0')
			spec->flags.zero = 1;
		else if (*ctx->cursor == '#')
			spec->flags.alternate = 1;
		else if (*ctx->cursor == ' ')
			spec->flags.space = 1;
		else if (*ctx->cursor == '+')
			spec->flags.plus = 1;
		else
			return ;
		ctx->cursor++;
	}
}

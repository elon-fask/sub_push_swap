/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_emit_text_field.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 04:24:47 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 04:24:47 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int	ft_emit_text_field(t_output *out, const t_format_spec *spec,
		const t_text_repr *repr)
{
	size_t	padding;

	padding = 0;
	if (spec->width > repr->length)
		padding = spec->width - repr->length;
	if (!spec->flags.left && ft_output_repeat(out, ' ', padding) < 0)
		return (-1);
	if (ft_output_write(out, repr->data, repr->length) < 0)
		return (-1);
	if (spec->flags.left)
		return (ft_output_repeat(out, ' ', padding));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_directive.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:52:37 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 02:12:22 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int	ft_process_directive(t_context *ctx)
{
	t_format_spec	spec;

	spec = (t_format_spec){0};
	if (ft_parse_directive(ctx, &spec) < 0)
		return (-1);
	return (ft_dispatch_conversion(ctx, &spec));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 01:56:21 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 02:08:28 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include <limits.h>

int	ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_context	ctx;
	int			status;

	if (!format)
		return (-1);
	ctx.cursor = format;
	ctx.output.fd = fd;
	ctx.output.count = 0;
	ctx.output.failed = false;
	va_copy(ctx.args, ap);
	status = ft_process_format(&ctx);
	va_end(ctx.args);
	if (status < 0 || ctx.output.failed)
		return (-1);
	if (ctx.output.count > (size_t)INT_MAX)
		return (-1);
	return ((int)ctx.output.count);
}

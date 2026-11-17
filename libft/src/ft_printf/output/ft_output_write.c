/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:52:53 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 02:59:45 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int	ft_output_write(t_output *out, const void *buffer, size_t length)
{
	if (out->failed)
		return (-1);
	if (length == 0)
		return (0);
	if (!buffer || length > SIZE_MAX - out->count)
	{
		out->failed = true;
		return (-1);
	}
	if (ft_write_all(out->fd, buffer, length) < 0)
	{
		out->failed = true;
		return (-1);
	}
	out->count += length;
	return (0);
}

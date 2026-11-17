/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 23:16:18 by eallam            #+#    #+#             */
/*   Updated: 2026/11/09 23:47:50 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

static void	ft_copy_forward(unsigned char *d, const unsigned char *s,
		size_t len)
{
	while (len > 0)
	{
		*d++ = *s++;
		len--;
	}
}

static void	ft_copy_backward(unsigned char *d, const unsigned char *s,
		size_t len)
{
	d += len;
	s += len;
	while (len > 0)
	{
		len--;
		*--d = *--s;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (len == 0 || dst == src)
		return (dst);
	if (!dst || !src)
		return (NULL);
	d = dst;
	s = src;
	if ((uintptr_t)d > (uintptr_t)s)
		ft_copy_backward(d, s, len);
	else
		ft_copy_forward(d, s, len);
	return (dst);
}

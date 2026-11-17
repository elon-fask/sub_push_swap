/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 08:53:16 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 03:22:34 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	length;

	length = 0;
	while (length < maxlen && s[length])
		length++;
	return (length);
}

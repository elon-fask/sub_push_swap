/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 22:59:56 by eallam            #+#    #+#             */
/*   Updated: 2026/11/09 23:00:08 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const unsigned char	*p;
	const unsigned char	*last;
	unsigned char		uc;

	p = (const unsigned char *)s;
	uc = (unsigned char)c;
	last = NULL;
	while (1)
	{
		if (*p == uc)
			last = p;
		if (*p == '\0')
			break ;
		p++;
	}
	return ((char *)last);
}

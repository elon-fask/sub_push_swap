/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 20:40:56 by eallam            #+#    #+#             */
/*   Updated: 2026/11/09 23:45:06 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

static int	ft_nbrlen(unsigned int nbr)
{
	int	len;

	len = 1;
	while (nbr >= 10)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nbr;
	int				len;
	bool			negative;

	negative = (n < 0);
	nbr = (unsigned int)n;
	if (negative)
		nbr = 0U - nbr;
	len = ft_nbrlen(nbr);
	str = malloc(sizeof(*str) * (negative + len + 1));
	if (!str)
		return (NULL);
	str[len + negative] = '\0';
	while (len > 0)
	{
		str[negative + --len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (negative)
		str[0] = '-';
	return (str);
}

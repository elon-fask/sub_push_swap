/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 21:18:21 by eallam            #+#    #+#             */
/*   Updated: 2026/11/12 21:18:53 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operands_internal.h"
#include <limits.h>

static int	parse_sign(const char **cursor)
{
	int	sign;

	sign = 1;
	if (**cursor == '+' || **cursor == '-')
	{
		if (**cursor == '-')
			sign = -1;
		++(*cursor);
	}
	return (sign);
}

static int	parse_magnitude(const char **cursor, unsigned long limit,
		unsigned long *magnitude)
{
	unsigned long	digit;

	*magnitude = 0;
	while (ft_isdigit((unsigned char)**cursor))
	{
		digit = (unsigned long)(**cursor - '0');
		if (*magnitude > (limit - digit) / 10UL)
			return (-1);
		*magnitude = *magnitude * 10UL + digit;
		++(*cursor);
	}
	return (0);
}

int	parse_integer(const char **cursor, int *value)
{
	unsigned long	magnitude;
	unsigned long	limit;
	int				sign;

	sign = parse_sign(cursor);
	if (!ft_isdigit((unsigned char)**cursor))
		return (-1);
	limit = (unsigned long)INT_MAX;
	if (sign < 0)
		limit = (unsigned long)(-(INT_MIN + 1)) + 1UL;
	if (parse_magnitude(cursor, limit, &magnitude) != 0)
		return (-1);
	if (**cursor && !ft_isspace((unsigned char)**cursor))
		return (-1);
	if (sign < 0 && magnitude == limit)
		*value = INT_MIN;
	else if (sign < 0)
		*value = -(int)magnitude;
	else
		*value = (int)magnitude;
	return (0);
}

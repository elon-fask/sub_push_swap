/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_operand_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 21:03:01 by eallam            #+#    #+#             */
/*   Updated: 2026/11/12 21:18:48 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operands_internal.h"

static size_t	count_argument_tokens(const char *arg)
{
	size_t	count;

	count = 0;
	while (*arg)
	{
		while (*arg && ft_isspace(*arg))
			++arg;
		if (*arg)
		{
			++count;
			while (*arg && !ft_isspace(*arg))
				++arg;
		}
	}
	return (count);
}

size_t	count_operand_tokens(const t_operands *operands)
{
	size_t	i;
	size_t	total;

	i = 0;
	total = 0;
	while (i < operands->count)
	{
		total += count_argument_tokens(operands->values[i]);
		++i;
	}
	return (total);
}

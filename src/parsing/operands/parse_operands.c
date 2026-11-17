/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 21:06:13 by eallam            #+#    #+#             */
/*   Updated: 2026/11/12 21:19:01 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operands_internal.h"

int	parse_operands(const t_operands *operands, t_stacks *stacks)
{
	size_t	i;
	size_t	total;

	total = count_operand_tokens(operands);
	if (total == 0 || initialize_stacks(stacks, total) != 0)
		return (-1);
	i = 0;
	while (i < operands->count)
	{
		if (parse_operand(operands->values[i], &stacks->a) != 0)
		{
			destroy_stacks(stacks);
			return (-1);
		}
		++i;
	}
	return (0);
}

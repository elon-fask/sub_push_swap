/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 21:06:22 by eallam            #+#    #+#             */
/*   Updated: 2026/11/16 12:43:47 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operands_internal.h"

static bool	contains_value(const t_stack *stack, int value)
{
	size_t	i;

	i = 0;
	while (i < stack->size)
	{
		if (stack->data[i] == value)
			return (true);
		++i;
	}
	return (false);
}

int	parse_operand(const char *arg, t_stack *stack)
{
	size_t	initial_size;
	int		value;

	initial_size = stack->size;
	while (*arg && ft_isspace((unsigned char)*arg))
		++arg;
	while (*arg)
	{
		if (parse_integer(&arg, &value) != 0)
			return (-1);
		if (contains_value(stack, value))
			return (-1);
		stack->data[stack->size] = value;
		++stack->size;
		while (*arg && ft_isspace((unsigned char)*arg))
			++arg;
	}
	if (stack->size == initial_size)
		return (-1);
	return (0);
}

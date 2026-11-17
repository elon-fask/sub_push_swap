/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "options_internal.h"
#include <stdlib.h>

int	initialize_parse_result(int argc, t_parse_result *result)
{
	size_t	capacity;

	result->options.strategy = STRATEGY_ADAPTIVE;
	result->options.strategy_explicit = false;
	result->options.benchmark_enabled = false;
	result->operands.values = NULL;
	result->operands.count = 0;
	result->operands.capacity = 0;
	capacity = (size_t)(argc - 1);
	if (capacity > (size_t)-1 / sizeof(*result->operands.values))
		return (-1);
	result->operands.values = malloc(capacity
			* sizeof(*result->operands.values));
	if (!result->operands.values)
		return (-1);
	result->operands.capacity = capacity;
	return (0);
}

void	destroy_parse_result(t_parse_result *result)
{
	free(result->operands.values);
	result->operands.values = NULL;
	result->operands.count = 0;
	result->operands.capacity = 0;
	result->options.strategy = STRATEGY_ADAPTIVE;
	result->options.strategy_explicit = false;
	result->options.benchmark_enabled = false;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 20:41:56 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "operands.h"
#include "options.h"
#include "push_swap_internal.h"
#include "stats.h"
#include <unistd.h>

static int	parse_input(int argc, char **argv, t_parse_result *result,
		t_context *context)
{
	if (parse_options(argc, argv, result) != 0)
		return (-1);
	if (parse_operands(&result->operands, &context->stacks) != 0)
	{
		destroy_parse_result(result);
		return (-1);
	}
	return (0);
}

static void	run_program(t_context *context, t_parse_result *result)
{
	init_stats(&context->stats, &result->options);
	orchestrator(context, &result->options);
	if (result->options.benchmark_enabled)
		print_benchmark(&context->stats);
}

int	main(int argc, char **argv)
{
	t_context		context;
	t_parse_result	result;

	if (argc == 1)
		return (0);
	if (parse_input(argc, argv, &result, &context) != 0)
	{
		ft_dprintf(STDERR_FILENO, "Error\n");
		return (1);
	}
	run_program(&context, &result);
	destroy_stacks(&context.stacks);
	destroy_parse_result(&result);
	return (0);
}

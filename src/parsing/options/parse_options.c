/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 04:23:09 by eallam            #+#    #+#             */
/*   Updated: 2026/11/14 22:20:33 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options_internal.h"

static int	run_parser(int argc, char **argv, t_parse_result *result)
{
	const t_option_spec	option_specs[] = {
	{'a', "adaptive", OPTION_SET_STRATEGY, STRATEGY_ADAPTIVE},
	{'s', "simple", OPTION_SET_STRATEGY, STRATEGY_SIMPLE},
	{'m', "medium", OPTION_SET_STRATEGY, STRATEGY_MEDIUM},
	{'c', "complex", OPTION_SET_STRATEGY, STRATEGY_COMPLEX},
	{'b', "bench", OPTION_ENABLE_BENCHMARK, STRATEGY_ADAPTIVE}
	};
	t_parse_context		context;

	context.argc = argc;
	context.argv = argv;
	context.result = result;
	context.option_registry.specs = option_specs;
	context.option_registry.count = sizeof(option_specs)
		/ sizeof(option_specs[0]);
	return (scan_arguments(&context));
}

int	parse_options(int argc, char **argv, t_parse_result *result)
{
	if (argc < 1)
		return (-1);
	if (initialize_parse_result(argc, result) != 0)
	{
		destroy_parse_result(result);
		return (-1);
	}
	if (run_parser(argc, argv, result) != 0)
	{
		destroy_parse_result(result);
		return (-1);
	}
	return (0);
}

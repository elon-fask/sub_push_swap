/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator_dispatch.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/16 15:50:31 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chunk.h"
#include "push_swap_internal.h"
#include "selection_sort.h"
#include "small_sort.h"
#include "sorting/disorder_ratio.h"
#include "turk.h"

double	record_disorder(t_context *context)
{
	double	disorder;

	disorder = calculate_disorder_ratio(&context->stacks.a);
	stats_set_disorder_ratio(&context->stats, disorder);
	return (disorder);
}

static t_strategy	select_adaptive_strategy(double disorder)
{
	if (disorder < 0.2)
		return (STRATEGY_SIMPLE);
	if (disorder < 0.5)
		return (STRATEGY_MEDIUM);
	return (STRATEGY_COMPLEX);
}

static void	execute_strategy(t_context *context, t_strategy strategy)
{
	if (strategy == STRATEGY_SIMPLE)
		selection_sort(context);
	else if (strategy == STRATEGY_MEDIUM)
		chunk_sort(context);
	else if (strategy == STRATEGY_COMPLEX)
		turk_sort(context);
}

void	dispatch_strategy(t_context *context, const t_program_options *options)
{
	t_strategy	strategy;
	double		disorder;

	strategy = options->strategy;
	if (options->strategy_explicit && strategy != STRATEGY_ADAPTIVE)
	{
		if (options->benchmark_enabled)
			record_disorder(context);
	}
	else if (strategy == STRATEGY_ADAPTIVE || options->benchmark_enabled)
	{
		disorder = record_disorder(context);
		if (strategy == STRATEGY_ADAPTIVE)
			strategy = select_adaptive_strategy(disorder);
	}
	stats_set_selected_strategy(&context->stats, strategy);
	execute_strategy(context, strategy);
}

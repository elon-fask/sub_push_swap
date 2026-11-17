/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 06:09:34 by eallam            #+#    #+#             */
/*   Updated: 2026/11/14 21:59:05 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stats.h"

void	init_stats(t_stats *stats, const t_program_options *options)
{
	size_t	i;

	stats->strategy_requested = options->strategy;
	stats->strategy_selected = STRATEGY_SIMPLE;
	if (options->strategy != STRATEGY_ADAPTIVE)
		stats->strategy_selected = options->strategy;
	stats->initial_disorder_ratio = 0.0;
	i = 0;
	while (i < OPERATION_COUNT)
	{
		stats->operation_counts[i] = 0;
		i++;
	}
}

void	stats_set_selected_strategy(t_stats *stats, t_strategy strategy)
{
	stats->strategy_selected = strategy;
}

void	stats_set_disorder_ratio(t_stats *stats, double disorder_ratio)
{
	stats->initial_disorder_ratio = disorder_ratio;
}

void	record_operation(t_stats *stats, t_operation operation)
{
	++stats->operation_counts[operation];
}

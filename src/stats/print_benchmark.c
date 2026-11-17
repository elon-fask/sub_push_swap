/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_benchmark.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "stats.h"
#include <unistd.h>

static const char	*get_strategy_name(t_strategy strategy)
{
	if (strategy == STRATEGY_ADAPTIVE)
		return ("adaptive");
	if (strategy == STRATEGY_SIMPLE)
		return ("simple");
	if (strategy == STRATEGY_MEDIUM)
		return ("medium");
	if (strategy == STRATEGY_COMPLEX)
		return ("complex");
	return ("unknown");
}

static const char	*get_strategy_complexity(t_strategy strategy)
{
	if (strategy == STRATEGY_SIMPLE)
		return ("O(n^2)");
	if (strategy == STRATEGY_MEDIUM)
		return ("O(n sqrt(n))");
	if (strategy == STRATEGY_COMPLEX)
		return ("O(n log n)");
	return ("unknown");
}

static void	print_disorder(double disorder_ratio)
{
	unsigned int	scaled;
	unsigned int	fraction;

	scaled = (unsigned int)(disorder_ratio * 10000.0 + 0.5);
	fraction = scaled % 100;
	ft_dprintf(STDERR_FILENO, "[bench] disorder: %u.%02u%%\n", scaled / 100,
		fraction);
}

static void	print_operation_counts(const t_stats *stats)
{
	ft_dprintf(STDERR_FILENO, "[bench] sa: %u  sb: %u  ss: %u\n",
		(unsigned int)stats->operation_counts[OPERATION_SA],
		(unsigned int)stats->operation_counts[OPERATION_SB],
		(unsigned int)stats->operation_counts[OPERATION_SS]);
	ft_dprintf(STDERR_FILENO, "[bench] pa: %u  pb: %u\n",
		(unsigned int)stats->operation_counts[OPERATION_PA],
		(unsigned int)stats->operation_counts[OPERATION_PB]);
	ft_dprintf(STDERR_FILENO, "[bench] ra: %u  rb: %u  rr: %u\n",
		(unsigned int)stats->operation_counts[OPERATION_RA],
		(unsigned int)stats->operation_counts[OPERATION_RB],
		(unsigned int)stats->operation_counts[OPERATION_RR]);
	ft_dprintf(STDERR_FILENO, "[bench] rra: %u rrb: %u rrr: %u\n",
		(unsigned int)stats->operation_counts[OPERATION_RRA],
		(unsigned int)stats->operation_counts[OPERATION_RRB],
		(unsigned int)stats->operation_counts[OPERATION_RRR]);
}

void	print_benchmark(const t_stats *stats)
{
	size_t	i;
	size_t	total;

	i = 0;
	total = 0;
	while (i < OPERATION_COUNT)
	{
		total += stats->operation_counts[i];
		++i;
	}
	print_disorder(stats->initial_disorder_ratio);
	if (stats->strategy_requested != stats->strategy_selected)
		ft_dprintf(STDERR_FILENO, "[bench] strategy: %s -> %s / %s\n",
			get_strategy_name(stats->strategy_requested),
			get_strategy_name(stats->strategy_selected),
			get_strategy_complexity(stats->strategy_selected));
	else
		ft_dprintf(STDERR_FILENO, "[bench] strategy: %s / %s\n",
			get_strategy_name(stats->strategy_selected),
			get_strategy_complexity(stats->strategy_selected));
	ft_dprintf(STDERR_FILENO, "[bench] total ops: %u\n",
		(unsigned int)total);
	print_operation_counts(stats);
}

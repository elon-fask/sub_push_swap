/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 04:42:04 by eallam            #+#    #+#             */
/*   Updated: 2026/11/14 22:08:43 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATS_H
# define STATS_H

# include <stddef.h>
# include "options.h"

typedef enum e_operation
{
	OPERATION_SA,
	OPERATION_SB,
	OPERATION_SS,
	OPERATION_PA,
	OPERATION_PB,
	OPERATION_RA,
	OPERATION_RB,
	OPERATION_RR,
	OPERATION_RRA,
	OPERATION_RRB,
	OPERATION_RRR,
	OPERATION_COUNT
}				t_operation;

typedef struct s_stats
{
	t_strategy	strategy_requested;
	t_strategy	strategy_selected;
	double		initial_disorder_ratio;
	size_t		operation_counts[OPERATION_COUNT];
}				t_stats;

void			init_stats(t_stats *stats,
					const t_program_options *options);
void			stats_set_selected_strategy(t_stats *stats,
					t_strategy strategy);
void			stats_set_disorder_ratio(t_stats *stats, double disorder_ratio);
void			record_operation(t_stats *stats, t_operation operation);
void			print_benchmark(const t_stats *stats);

#endif /* STATS_H */

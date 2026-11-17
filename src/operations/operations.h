/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 04:57:24 by eallam            #+#    #+#             */
/*   Updated: 2026/11/13 04:57:27 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "stack.h"
# include "stats.h"

t_stack_status	operation_pa(t_stacks *stacks, t_stats *stats);
t_stack_status	operation_pb(t_stacks *stacks, t_stats *stats);

t_stack_status	operation_rra(t_stack *a, t_stats *stats);
t_stack_status	operation_rrb(t_stack *b, t_stats *stats);
t_stack_status	operation_rrr(t_stacks *stacks, t_stats *stats);

t_stack_status	operation_ra(t_stack *a, t_stats *stats);
t_stack_status	operation_rb(t_stack *b, t_stats *stats);
t_stack_status	operation_rr(t_stacks *stacks, t_stats *stats);

t_stack_status	operation_sa(t_stack *a, t_stats *stats);
t_stack_status	operation_sb(t_stack *b, t_stats *stats);
t_stack_status	operation_ss(t_stacks *stacks, t_stats *stats);

#endif /* OPERATIONS_H */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_reverse_rotate.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 05:14:21 by eallam            #+#    #+#             */
/*   Updated: 2026/11/13 04:55:06 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "operations.h"

t_stack_status	operation_rra(t_stack *a, t_stats *stats)
{
	t_stack_status	status;

	status = stack_reverse_rotate(a);
	if (status == STACK_UNCHANGED)
		return (STACK_UNCHANGED);
	ft_printf("rra\n");
	record_operation(stats, OPERATION_RRA);
	return (STACK_CHANGED);
}

t_stack_status	operation_rrb(t_stack *b, t_stats *stats)
{
	t_stack_status	status;

	status = stack_reverse_rotate(b);
	if (status == STACK_UNCHANGED)
		return (STACK_UNCHANGED);
	ft_printf("rrb\n");
	record_operation(stats, OPERATION_RRB);
	return (STACK_CHANGED);
}

t_stack_status	operation_rrr(t_stacks *stacks, t_stats *stats)
{
	t_stack_status	status_a;
	t_stack_status	status_b;

	status_a = stack_reverse_rotate(&stacks->a);
	status_b = stack_reverse_rotate(&stacks->b);
	if (status_a == STACK_UNCHANGED && status_b == STACK_UNCHANGED)
		return (STACK_UNCHANGED);
	ft_printf("rrr\n");
	record_operation(stats, OPERATION_RRR);
	return (STACK_CHANGED);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 05:14:24 by eallam            #+#    #+#             */
/*   Updated: 2026/11/13 04:55:15 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "operations.h"

t_stack_status	operation_ra(t_stack *a, t_stats *stats)
{
	t_stack_status	status;

	status = stack_rotate(a);
	if (status == STACK_UNCHANGED)
		return (STACK_UNCHANGED);
	ft_printf("ra\n");
	record_operation(stats, OPERATION_RA);
	return (STACK_CHANGED);
}

t_stack_status	operation_rb(t_stack *b, t_stats *stats)
{
	t_stack_status	status;

	status = stack_rotate(b);
	if (status == STACK_UNCHANGED)
		return (STACK_UNCHANGED);
	ft_printf("rb\n");
	record_operation(stats, OPERATION_RB);
	return (STACK_CHANGED);
}

t_stack_status	operation_rr(t_stacks *stacks, t_stats *stats)
{
	t_stack_status	status_a;
	t_stack_status	status_b;

	status_a = stack_rotate(&stacks->a);
	status_b = stack_rotate(&stacks->b);
	if (status_a == STACK_UNCHANGED && status_b == STACK_UNCHANGED)
		return (STACK_UNCHANGED);
	ft_printf("rr\n");
	record_operation(stats, OPERATION_RR);
	return (STACK_CHANGED);
}

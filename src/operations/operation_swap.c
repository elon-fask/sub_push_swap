/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 05:14:27 by eallam            #+#    #+#             */
/*   Updated: 2026/11/13 04:55:21 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "operations.h"

t_stack_status	operation_sa(t_stack *a, t_stats *stats)
{
	t_stack_status	status;

	status = stack_swap_top(a);
	if (status == STACK_UNCHANGED)
		return (STACK_UNCHANGED);
	ft_printf("sa\n");
	record_operation(stats, OPERATION_SA);
	return (STACK_CHANGED);
}

t_stack_status	operation_sb(t_stack *b, t_stats *stats)
{
	t_stack_status	status;

	status = stack_swap_top(b);
	if (status == STACK_UNCHANGED)
		return (STACK_UNCHANGED);
	ft_printf("sb\n");
	record_operation(stats, OPERATION_SB);
	return (STACK_CHANGED);
}

t_stack_status	operation_ss(t_stacks *stacks, t_stats *stats)
{
	t_stack_status	status_a;
	t_stack_status	status_b;

	status_a = stack_swap_top(&stacks->a);
	status_b = stack_swap_top(&stacks->b);
	if (status_a == STACK_UNCHANGED && status_b == STACK_UNCHANGED)
		return (STACK_UNCHANGED);
	ft_printf("ss\n");
	record_operation(stats, OPERATION_SS);
	return (STACK_CHANGED);
}

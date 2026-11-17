/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_push.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 05:14:19 by eallam            #+#    #+#             */
/*   Updated: 2026/11/13 04:54:37 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "operations.h"

t_stack_status	operation_pa(t_stacks *stacks, t_stats *stats)
{
	int				value;

	if (stack_pop_top(&stacks->b, &value) == STACK_UNCHANGED)
		return (STACK_UNCHANGED);
	stack_push_top(&stacks->a, value);
	ft_printf("pa\n");
	record_operation(stats, OPERATION_PA);
	return (STACK_CHANGED);
}

t_stack_status	operation_pb(t_stacks *stacks, t_stats *stats)
{
	int				value;

	if (stack_pop_top(&stacks->a, &value) == STACK_UNCHANGED)
		return (STACK_UNCHANGED);
	stack_push_top(&stacks->b, value);
	ft_printf("pb\n");
	record_operation(stats, OPERATION_PB);
	return (STACK_CHANGED);
}

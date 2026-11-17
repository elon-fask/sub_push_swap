/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_small_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "turk_internal.h"
#include "sorting_utils.h"

static void	sort_descending(t_context *context)
{
	operation_sa(&context->stacks.a, &context->stats);
	operation_rra(&context->stacks.a, &context->stats);
}

static void	sort_middle_value(t_context *context, int first, int third)
{
	if (first < third)
	{
		operation_sa(&context->stacks.a, &context->stats);
		operation_ra(&context->stacks.a, &context->stats);
	}
	else
		operation_rra(&context->stacks.a, &context->stats);
}

static void	sort_three(t_context *context)
{
	int	first;
	int	second;
	int	third;

	first = sorting_value_at(&context->stacks.a, 0);
	second = sorting_value_at(&context->stacks.a, 1);
	third = sorting_value_at(&context->stacks.a, 2);
	if (first > second && second > third)
		sort_descending(context);
	else if (first > second && first > third)
		operation_ra(&context->stacks.a, &context->stats);
	else if (second > third)
		sort_middle_value(context, first, third);
	else if (first > second)
		operation_sa(&context->stacks.a, &context->stats);
}

void	turk_sort_small(t_context *context)
{
	sort_three(context);
}

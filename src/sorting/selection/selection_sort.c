/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/16 15:51:06 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "selection_sort.h"
#include "small_sort.h"
#include "sorting_utils.h"

void	selection_sort(t_context *context)
{
	if (context->stacks.a.size <= 5)
	{
		small_sort(context);
		return ;
	}
	while (context->stacks.a.size > 0)
	{
		sorting_rotate_to_offset(context, &context->stacks.a,
			sorting_minimum_offset(&context->stacks.a), false);
		operation_pb(&context->stacks, &context->stats);
	}
	while (context->stacks.b.size > 0)
		operation_pa(&context->stacks, &context->stats);
}

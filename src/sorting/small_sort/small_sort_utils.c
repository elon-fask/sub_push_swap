/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "small_sort_internal.h"
#include "sorting_utils.h"

void	sort_two(t_context *context)
{
	int	first;
	int	second;

	first = sorting_value_at(&context->stacks.a, 0);
	second = sorting_value_at(&context->stacks.a, 1);
	if (first > second)
		operation_sa(&context->stacks.a, &context->stats);
}

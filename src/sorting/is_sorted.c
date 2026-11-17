/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sorted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 22:23:58 by eallam            #+#    #+#             */
/*   Updated: 2026/11/13 22:30:15 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_internal.h"
#include "sorting_utils.h"

bool	is_sorted(const t_stack *stack)
{
	size_t	i;
	int		current;
	int		next;

	i = 0;
	while (i + 1 < stack->size)
	{
		current = sorting_value_at(stack, i);
		next = sorting_value_at(stack, i + 1);
		if (current > next)
			return (false);
		++i;
	}
	return (true);
}

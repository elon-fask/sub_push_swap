/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder_ratio.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 20:37:11 by eallam            #+#    #+#             */
/*   Updated: 2026/11/11 15:12:13 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disorder_ratio.h"

double	calculate_disorder_ratio(const t_stack *stack)
{
	size_t	inversions;
	size_t	total_pairs;
	size_t	i;
	size_t	j;

	inversions = 0;
	total_pairs = 0;
	i = 0;
	while (i < stack->size)
	{
		j = i + 1;
		while (j < stack->size)
		{
			++total_pairs;
			if (stack->data[i] > stack->data[j])
				++inversions;
			++j;
		}
		++i;
	}
	return ((double)inversions / total_pairs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_stacks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "stack.h"
#include <stdint.h>
#include <stdlib.h>

int	initialize_stacks(t_stacks *stacks, size_t capacity)
{
	*stacks = (t_stacks){0};
	if (capacity > SIZE_MAX / sizeof(*stacks->a.data))
		return (-1);
	stacks->a.data = malloc(capacity * sizeof(*stacks->a.data));
	if (!stacks->a.data)
		return (-1);
	stacks->b.data = malloc(capacity * sizeof(*stacks->b.data));
	if (!stacks->b.data)
	{
		free(stacks->a.data);
		stacks->a.data = NULL;
		return (-1);
	}
	stacks->a.head = 0;
	stacks->a.size = 0;
	stacks->a.capacity = capacity;
	stacks->b.head = 0;
	stacks->b.size = 0;
	stacks->b.capacity = capacity;
	return (0);
}

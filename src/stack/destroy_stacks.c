/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_stacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "stack.h"
#include <stdlib.h>

void	destroy_stacks(t_stacks *stacks)
{
	free(stacks->a.data);
	free(stacks->b.data);
	stacks->a.data = NULL;
	stacks->b.data = NULL;
	stacks->a.head = 0;
	stacks->b.head = 0;
	stacks->a.size = 0;
	stacks->b.size = 0;
	stacks->a.capacity = 0;
	stacks->b.capacity = 0;
}

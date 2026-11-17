/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_push_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 16:57:57 by eallam            #+#    #+#             */
/*   Updated: 2026/11/12 16:57:58 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_internal_bonus.h"
#include "libft.h"

static int	transfer_top(t_stack *src, t_stack *dst)
{
	int	value;

	if (stack_pop_top(src, &value) == STACK_UNCHANGED)
		return (0);
	stack_push_top(dst, value);
	return (0);
}

int	execute_push(t_stacks *stacks, const char *line)
{
	if (ft_strcmp(line, "pa") == 0)
		return (transfer_top(&stacks->b, &stacks->a));
	if (ft_strcmp(line, "pb") == 0)
		return (transfer_top(&stacks->a, &stacks->b));
	return (-1);
}

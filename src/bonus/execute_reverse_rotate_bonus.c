/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_reverse_rotate_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 16:57:59 by eallam            #+#    #+#             */
/*   Updated: 2026/11/12 16:58:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_internal_bonus.h"
#include "libft.h"

int	execute_reverse_rotate(t_stacks *stacks, const char *line)
{
	if (ft_strcmp(line, "rra") == 0)
		stack_reverse_rotate(&stacks->a);
	else if (ft_strcmp(line, "rrb") == 0)
		stack_reverse_rotate(&stacks->b);
	else if (ft_strcmp(line, "rrr") == 0)
	{
		stack_reverse_rotate(&stacks->a);
		stack_reverse_rotate(&stacks->b);
	}
	else
		return (-1);
	return (0);
}

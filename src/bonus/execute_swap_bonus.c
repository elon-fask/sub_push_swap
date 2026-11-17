/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_swap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 16:58:04 by eallam            #+#    #+#             */
/*   Updated: 2026/11/12 16:58:05 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_internal_bonus.h"
#include "libft.h"

int	execute_swap(t_stacks *stacks, const char *line)
{
	if (ft_strcmp(line, "sa") == 0)
		stack_swap_top(&stacks->a);
	else if (ft_strcmp(line, "sb") == 0)
		stack_swap_top(&stacks->b);
	else if (ft_strcmp(line, "ss") == 0)
	{
		stack_swap_top(&stacks->a);
		stack_swap_top(&stacks->b);
	}
	else
		return (-1);
	return (0);
}

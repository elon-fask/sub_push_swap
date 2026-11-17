/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_rotate_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 16:58:02 by eallam            #+#    #+#             */
/*   Updated: 2026/11/12 16:58:02 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_internal_bonus.h"
#include "libft.h"

int	execute_rotate(t_stacks *stacks, const char *line)
{
	if (ft_strcmp(line, "ra") == 0)
		stack_rotate(&stacks->a);
	else if (ft_strcmp(line, "rb") == 0)
		stack_rotate(&stacks->b);
	else if (ft_strcmp(line, "rr") == 0)
	{
		stack_rotate(&stacks->a);
		stack_rotate(&stacks->b);
	}
	else
		return (-1);
	return (0);
}

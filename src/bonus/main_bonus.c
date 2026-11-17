/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 20:37:05 by eallam            #+#    #+#             */
/*   Updated: 2026/11/14 19:08:50 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_internal_bonus.h"
#include "ft_printf.h"
#include "operands.h"
#include "push_swap_internal.h"
#include "unistd.h"

int	main(int argc, char **argv)
{
	t_operands	operands;
	t_stacks	stacks;

	if (argc == 1)
		return (0);
	operands.count = argc - 1;
	operands.capacity = argc - 1;
	operands.values = argv + 1;
	if (parse_operands(&operands, &stacks) != 0)
	{
		ft_dprintf(STDERR_FILENO, "Error\n");
		return (1);
	}
	if (process_instructions(&stacks) != 0)
	{
		destroy_stacks(&stacks);
		ft_dprintf(STDERR_FILENO, "Error\n");
		return (1);
	}
	if (is_sorted(&stacks.a) && stacks.b.size == 0)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	destroy_stacks(&stacks);
	return (0);
}

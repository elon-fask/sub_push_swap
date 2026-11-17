/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_loop_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 16:57:54 by eallam            #+#    #+#             */
/*   Updated: 2026/11/16 18:05:43 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_internal_bonus.h"
#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int	process_instructions(t_stacks *stacks)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (execute_instruction(stacks, line) != 0)
		{
			free(line);
			get_next_line_cleanup();
			return (-1);
		}
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	if (get_next_line_has_error())
		return (-1);
	return (0);
}

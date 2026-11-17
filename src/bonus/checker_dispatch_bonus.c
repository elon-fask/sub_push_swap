/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_dispatch_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 16:57:52 by eallam            #+#    #+#             */
/*   Updated: 2026/11/12 16:57:53 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_internal_bonus.h"
#include "libft.h"

int	execute_instruction(t_stacks *stacks, char *line)
{
	size_t	length;

	length = ft_strlen(line);
	if (length > 0 && line[length - 1] == '\n')
		line[length - 1] = '\0';
	if (line[0] == 's')
		return (execute_swap(stacks, line));
	if (line[0] == 'p')
		return (execute_push(stacks, line));
	if (line[0] == 'r' && line[1] == 'r' && line[2] != '\0')
		return (execute_reverse_rotate(stacks, line));
	if (line[0] == 'r')
		return (execute_rotate(stacks, line));
	return (-1);
}

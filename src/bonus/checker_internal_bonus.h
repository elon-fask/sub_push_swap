/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_internal_bonus.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 18:47:55 by eallam            #+#    #+#             */
/*   Updated: 2026/11/12 17:21:37 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_INTERNAL_BONUS_H
# define CHECKER_INTERNAL_BONUS_H

# include "stack.h"

int		process_instructions(t_stacks *stacks);
int		execute_instruction(t_stacks *stacks, char *line);

int		execute_push(t_stacks *stacks, const char *line);
int		execute_swap(t_stacks *stacks, const char *line);
int		execute_rotate(t_stacks *stacks, const char *line);
int		execute_reverse_rotate(t_stacks *stacks, const char *line);

#endif /* CHECKER_INTERNAL_BONUS_H */

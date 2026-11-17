/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 18:47:55 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stddef.h>

typedef struct s_stack
{
	int			*data;
	size_t		capacity;
	size_t		head;
	size_t		size;
}				t_stack;

typedef struct s_stacks
{
	t_stack		a;
	t_stack		b;
}				t_stacks;

typedef enum e_stack_status
{
	STACK_UNCHANGED,
	STACK_CHANGED
}				t_stack_status;

int				initialize_stacks(t_stacks *stacks, size_t capacity);
void			destroy_stacks(t_stacks *stacks);
t_stack_status	stack_pop_top(t_stack *stack, int *popped_value);
t_stack_status	stack_push_top(t_stack *stack, int new_value);
t_stack_status	stack_reverse_rotate(t_stack *stack);
t_stack_status	stack_rotate(t_stack *stack);
t_stack_status	stack_swap_top(t_stack *stack);

#endif /* STACK_H */

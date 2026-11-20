/* ************************************************************************** */
/*  src/stack/stack.c — circular ring-buffer primitives (no libft)            */
/*  Faithful rebuild of: initialize_stacks/destroy_stacks, push_top, pop_top, */
/*  swap_top, rotate, reverse_rotate + lookup helpers.                        */
/* ************************************************************************** */
#include "psw.h"
#include <stdlib.h>
#include <stdint.h>

/* Allocate both ring buffers. Capacity equals the total input token count. */
bool	init_stacks(t_stacks *stacks, size_t capacity)
{
	if (capacity == 0)
		capacity = 1;
	if (capacity > SIZE_MAX / sizeof(int))
		return (false);
	stacks->a.data = malloc(capacity * sizeof(int));
	stacks->b.data = malloc(capacity * sizeof(int));
	if (!stacks->a.data || !stacks->b.data)
	{
		free(stacks->a.data);
		free(stacks->b.data);
		stacks->a.data = NULL;
		stacks->b.data = NULL;
		return (false);
	}
	stacks->a.capacity = capacity;
	stacks->b.capacity = capacity;
	stacks->a.head = 0;
	stacks->b.head = 0;
	stacks->a.size = 0;
	stacks->b.size = 0;
	return (true);
}

void	free_stacks(t_stacks *stacks)
{
	free(stacks->a.data);
	free(stacks->b.data);
	stacks->a.data = NULL;
	stacks->b.data = NULL;
}

/* Push a new value on TOP: move head backward (counter-clockwise), write. */
bool	push_top(t_stack *stack, int value)
{
	if (stack->size == stack->capacity)
		return (false);
	if (stack->head == 0)
		stack->head = stack->capacity - 1;
	else
		--stack->head;
	stack->data[stack->head] = value;
	++stack->size;
	return (true);
}

/* Pop the TOP value: read data[head], move head forward (clockwise).      */
bool	pop_top(t_stack *stack, int *value)
{
	if (stack->size == 0)
		return (false);
	*value = stack->data[stack->head];
	++stack->head;
	if (stack->head == stack->capacity)
		stack->head = 0;
	--stack->size;
	return (true);
}

/* Swap top two logical elements; head and size unchanged.                 */
bool	swap_top(t_stack *stack)
{
	size_t	second;
	int		tmp;

	if (stack->size < 2)
		return (false);
	second = stack->head + 1;
	if (second == stack->capacity)
		second = 0;
	tmp = stack->data[stack->head];
	stack->data[stack->head] = stack->data[second];
	stack->data[second] = tmp;
	return (true);
}

/* ra / rb: old top becomes the new bottom. Head advances; old top copied  */
/* into the new bottom slot (head + size - 1) % capacity.                 */
bool	rotate(t_stack *stack)
{
	int		top_value;
	size_t	bottom_index;

	if (stack->size < 2)
		return (false);
	top_value = stack->data[stack->head];
	++stack->head;
	if (stack->head == stack->capacity)
		stack->head = 0;
	bottom_index = (stack->head + stack->size - 1) % stack->capacity;
	stack->data[bottom_index] = top_value;
	return (true);
}

/* rra / rrb: old bottom becomes the new top. Head moves backward; bottom  */
/* value copied into the new head slot.                                    */
bool	reverse_rotate(t_stack *stack)
{
	int		bottom_value;
	size_t	bottom_index;

	if (stack->size < 2)
		return (false);
	bottom_index = (stack->head + stack->size - 1) % stack->capacity;
	bottom_value = stack->data[bottom_index];
	if (stack->head == 0)
		stack->head = stack->capacity - 1;
	else
		--stack->head;
	stack->data[stack->head] = bottom_value;
	return (true);
}

/* ---------- lookup helpers (mirror src/sorting/utils/stack_lookup.c) --- */

int	value_at(const t_stack *stack, size_t offset)
{
	return (stack->data[(stack->head + offset) % stack->capacity]);
}

size_t	min_offset(const t_stack *stack)
{
	size_t	best = 0;
	size_t	i;

	for (i = 1; i < stack->size; ++i)
		if (value_at(stack, i) < value_at(stack, best))
			best = i;
	return (best);
}

size_t	max_offset(const t_stack *stack)
{
	size_t	best = 0;
	size_t	i;

	for (i = 1; i < stack->size; ++i)
		if (value_at(stack, i) > value_at(stack, best))
			best = i;
	return (best);
}

bool	is_sorted(const t_stack *stack)
{
	size_t	i;

	for (i = 0; i + 1 < stack->size; ++i)
		if (value_at(stack, i) > value_at(stack, i + 1))
			return (false);
	return (true);
}

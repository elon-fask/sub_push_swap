/* ************************************************************************** */
/*  src/operations/ops.c — printed operation wrappers (no libft)              */
/*  Each wrapper: call primitive -> if changed, print instruction on stdout  */
/*  and increment the matching stats counter. Combined ops print once.      */
/* ************************************************************************** */
#include "psw.h"
#include <unistd.h>

static void	record(t_stats *st, t_operation op)
{
	++st->count[op];
	++st->total;
}

void	op_pa(t_stacks *s, t_stats *st)
{
	int	value;

	if (!pop_top(&s->b, &value))
		return ;
	push_top(&s->a, value);
	write(1, "pa\n", 3);
	record(st, OP_PA);
}

void	op_pb(t_stacks *s, t_stats *st)
{
	int	value;

	if (!pop_top(&s->a, &value))
		return ;
	push_top(&s->b, value);
	write(1, "pb\n", 3);
	record(st, OP_PB);
}

void	op_sa(t_stack *a, t_stats *st)
{
	if (!swap_top(a))
		return ;
	write(1, "sa\n", 3);
	record(st, OP_SA);
}

void	op_sb(t_stack *b, t_stats *st)
{
	if (!swap_top(b))
		return ;
	write(1, "sb\n", 3);
	record(st, OP_SB);
}

void	op_ss(t_stacks *s, t_stats *st)
{
	bool	ca = swap_top(&s->a);
	bool	cb = swap_top(&s->b);

	if (!ca && !cb)
		return ;
	write(1, "ss\n", 3);
	record(st, OP_SS);
}

void	op_ra(t_stack *a, t_stats *st)
{
	if (!rotate(a))
		return ;
	write(1, "ra\n", 3);
	record(st, OP_RA);
}

void	op_rb(t_stack *b, t_stats *st)
{
	if (!rotate(b))
		return ;
	write(1, "rb\n", 3);
	record(st, OP_RB);
}

void	op_rr(t_stacks *s, t_stats *st)
{
	bool	ca = rotate(&s->a);
	bool	cb = rotate(&s->b);

	if (!ca && !cb)
		return ;
	write(1, "rr\n", 3);
	record(st, OP_RR);
}

void	op_rra(t_stack *a, t_stats *st)
{
	if (!reverse_rotate(a))
		return ;
	write(1, "rra\n", 4);
	record(st, OP_RRA);
}

void	op_rrb(t_stack *b, t_stats *st)
{
	if (!reverse_rotate(b))
		return ;
	write(1, "rrb\n", 4);
	record(st, OP_RRB);
}

void	op_rrr(t_stacks *s, t_stats *st)
{
	bool	ca = reverse_rotate(&s->a);
	bool	cb = reverse_rotate(&s->b);

	if (!ca && !cb)
		return ;
	write(1, "rrr\n", 4);
	record(st, OP_RRR);
}

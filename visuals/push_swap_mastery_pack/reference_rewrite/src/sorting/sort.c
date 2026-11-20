/* ************************************************************************** */
/*  src/sorting/sort.c — disorder metric, small sort, selection sort,        */
/*  adaptive dispatcher for the no-libft reference core.                    */
/*  Chunk and Turk advanced strategies ship as annotated stubs (not compiled */
/*  in this minimal core); see chunk_stub.c and turk_stub.c and docs.        */
/* ************************************************************************** */
#include "psw.h"
#include <unistd.h>
#include <stdio.h>

/* ---------------- disorder ratio (Kendall inversion density) ------------ */

double	disorder_ratio(const t_stack *stack)
{
	size_t	inversions = 0;
	size_t	total = 0;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < stack->size)
	{
		j = i + 1;
		while (j < stack->size)
		{
			++total;
			if (value_at(stack, i) > value_at(stack, j))
				++inversions;
			++j;
		}
		++i;
	}
	if (total == 0)
		return (0.0);
	return ((double)inversions / (double)total);
}

/* ---------------- bring an offset to the top on the shortest path ------ */

static void	rotate_to_top(t_stacks *s, t_stack *stack, size_t offset,
		t_stats *st)
{
	size_t	forward = offset;
	size_t	reverse = stack->size - offset;

	if (forward < reverse)
	{
		while (forward-- > 0)
		{
			if (stack == &s->a)
				op_ra(&s->a, st);
			else
				op_rb(&s->b, st);
		}
	}
	else
	{
		while (reverse-- > 0)
		{
			if (stack == &s->a)
				op_rra(&s->a, st);
			else
				op_rrb(&s->b, st);
		}
	}
}

/* ---------------- small sort: N <= 5 (mirrors sort_two/three/five) ----- */

static void	sort_two(t_stacks *s, t_stats *st)
{
	if (value_at(&s->a, 0) > value_at(&s->a, 1))
		op_sa(&s->a, st);
}

static void	sort_three(t_stacks *s, t_stats *st)
{
	size_t	max_off = max_offset(&s->a);

	if (max_off == 0)
		op_ra(&s->a, st);
	else if (max_off == 1)
		op_rra(&s->a, st);
	if (value_at(&s->a, 0) > value_at(&s->a, 1))
		op_sa(&s->a, st);
}

static void	move_min_to_b(t_stacks *s, t_stats *st)
{
	rotate_to_top(s, &s->a, min_offset(&s->a), st);
	op_pb(s, st);
}

void	small_sort(t_stacks *s, t_stats *st)
{
	if (s->a.size <= 1)
		return ;
	if (s->a.size == 2)
	{
		sort_two(s, st);
		return ;
	}
	while (s->a.size > 3)
		move_min_to_b(s, st);
	sort_three(s, st);
	while (s->b.size > 0)
		op_pa(s, st);
}

/* ---------------- simple strategy: selection sort ---------------------- */

void	selection_sort(t_stacks *s, t_stats *st)
{
	if (s->a.size <= 5)
	{
		small_sort(s, st);
		return ;
	}
	while (s->a.size > 0)
	{
		rotate_to_top(s, &s->a, min_offset(&s->a), st);
		op_pb(s, st);
	}
	while (s->b.size > 0)
		op_pa(s, st);
}

/* Advanced strategies present in the real project; annotated as stubs.    */
void	chunk_sort(t_stacks *s, t_stats *st) { (void)s; (void)st; }
void	turk_sort(t_stacks *s, t_stats *st) { (void)s; (void)st; }

/* ---------------- dispatcher (mirrors orchestrator.c) ------------------- */

static void	print_bench(t_strategy chosen, double disorder, const t_stats *st)
{
	const char	*name[] = { "auto", "simple", "medium", "complex" };
	char		buf[64];
	int			n;

	n = snprintf(buf, sizeof(buf),
		"[bench] disorder: %.2f%%  strategy: %s  total ops: %zu\n",
		disorder * 100.0, name[chosen], st->total);
	if (n > 0)
		write(2, buf, (size_t)n);
}

void	run_solver(t_stacks *s, t_stats *st, t_strategy forced, bool bench)
{
	double		disorder;
	t_strategy	chosen;

	if (is_sorted(&s->a))
		return ;
	disorder = disorder_ratio(&s->a);
	chosen = forced;
	if (chosen == STRAT_AUTO)
	{
		if (disorder < 0.2)
			chosen = STRAT_SIMPLE;
		else if (disorder < 0.5)
			chosen = STRAT_MEDIUM;
		else
			chosen = STRAT_COMPLEX;
	}
	if (chosen == STRAT_SIMPLE)
		selection_sort(s, st);
	else
		/* Minimal core: advanced strategies are documented in the stubs. */
		selection_sort(s, st);
	if (bench)
		print_bench(chosen, disorder, st);
}

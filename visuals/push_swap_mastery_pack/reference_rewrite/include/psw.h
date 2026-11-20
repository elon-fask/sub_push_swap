/* ************************************************************************** */
/*  psw.h — single public header for the no-libft reference rewrite          */
/*  Same architecture as the teammate's project, rebuilt with only libc.      */
/*  Replacement map:                                                          */
/*    ft_printf("pa\n")      -> write(1, "pa\n", 3)                           */
/*    ft_dprintf(2,"Error\n") -> write(2, "Error\n", 6)                        */
/*    ft_strcmp(a,b)         -> strcmp(a,b)            (<string.h>)          */
/*    ft_isspace/isdigit     -> isspace/isdigit        (<ctype.h>)            */
/*    ft_strlen(s)           -> strlen(s)              (<string.h>)            */
/*    ft_calloc(n,sz)         -> calloc(n,sz)         (<stdlib.h>)            */
/*    get_next_line(fd)       -> read_line(fd) (checker only, not in core)    */
/* ************************************************************************** */
#ifndef PSW_H
# define PSW_H

# include <stdbool.h>
# include <stddef.h>

/* ---------------- data structures ---------------- */

typedef struct s_stack
{
	int		*data;        /* contiguous ring buffer                    */
	size_t	capacity;    /* total slots (= number of input integers)  */
	size_t	head;         /* physical index of the TOP element         */
	size_t	size;         /* number of active elements                 */
}	t_stack;

typedef struct s_stacks
{
	t_stack	a;
	t_stack	b;
}	t_stacks;

typedef enum e_operation
{
	OP_SA, OP_SB, OP_SS,
	OP_PA, OP_PB,
	OP_RA, OP_RB, OP_RR,
	OP_RRA, OP_RRB, OP_RRR,
	OP_COUNT
}	t_operation;

typedef struct s_stats
{
	size_t	count[OP_COUNT];
	size_t	total;
}	t_stats;

typedef enum e_strategy
{
	STRAT_AUTO, STRAT_SIMPLE, STRAT_MEDIUM, STRAT_COMPLEX
}	t_strategy;

/* ---------------- stack primitives (src/stack) ---------------- */

bool	init_stacks(t_stacks *stacks, size_t capacity);
void	free_stacks(t_stacks *stacks);

bool	push_top(t_stack *stack, int value);          /* pa/pb source side */
bool	pop_top(t_stack *stack, int *value);           /* pa/pb source side */
bool	swap_top(t_stack *stack);                      /* sa/sb/ss          */
bool	rotate(t_stack *stack);                         /* ra/rb/rr          */
bool	reverse_rotate(t_stack *stack);                 /* rra/rrb/rrr       */

int		value_at(const t_stack *stack, size_t offset); /* logical offset 0 = top */
size_t	min_offset(const t_stack *stack);
size_t	max_offset(const t_stack *stack);
bool	is_sorted(const t_stack *stack);

/* ---------------- operations layer (src/operations) ---------------- */

void	op_pa(t_stacks *s, t_stats *st);
void	op_pb(t_stacks *s, t_stats *st);
void	op_sa(t_stack *a, t_stats *st);
void	op_sb(t_stack *b, t_stats *st);
void	op_ss(t_stacks *s, t_stats *st);
void	op_ra(t_stack *a, t_stats *st);
void	op_rb(t_stack *b, t_stats *st);
void	op_rr(t_stacks *s, t_stats *st);
void	op_rra(t_stack *a, t_stats *st);
void	op_rrb(t_stack *b, t_stats *st);
void	op_rrr(t_stacks *s, t_stats *st);

/* ---------------- parsing (src/parsing) ---------------- */

/* Parse argv into stacks->a. Returns 0 on success, -1 on any error.        */
/* Accepts numbers and simple flags: -s / -m / -c force a strategy, -b     */
/* enables benchmark on stderr. A token may contain several space-separated */
/* integers (e.g. "3 2 1"), like the real project.                         */
int		parse_input(int argc, char **argv, t_stacks *stacks,
				t_strategy *forced, bool *bench);

/* ---------------- sorting (src/sorting) ---------------- */

double	disorder_ratio(const t_stack *stack);
void	small_sort(t_stacks *s, t_stats *st);
void	selection_sort(t_stacks *s, t_stats *st);
void	chunk_sort(t_stacks *s, t_stats *st);   /* see annotated stub file */
void	turk_sort(t_stacks *s, t_stats *st);    /* see annotated stub file */
void	run_solver(t_stacks *s, t_stats *st, t_strategy forced, bool bench);

#endif

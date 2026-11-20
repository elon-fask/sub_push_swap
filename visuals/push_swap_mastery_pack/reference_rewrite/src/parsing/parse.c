/* ************************************************************************** */
/*  src/parsing/parse.c — options + overflow-safe integers + duplicates       */
/*  Replaces the teammate's parsing/options + parsing/operands layers.       */
/*  libc used: calloc/malloc-free via stack.c, ctype, string, limits.         */
/* ************************************************************************** */
#include "psw.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

/* Overflow-safe integer parse. Cursor advances past the consumed number.   */
/* Returns 0 on success, -1 on invalid token / out-of-range value.          */
static int	parse_integer(const char **cursor, int *out)
{
	unsigned long	magnitude;
	unsigned long	limit;
	int				sign;
	const char		*p;

	p = *cursor;
	sign = 1;
	if (*p == '-' || *p == '+')
	{
		if (*p == '-')
			sign = -1;
		++p;
	}
	if (!isdigit((unsigned char)*p))
		return (-1);
	limit = (unsigned long)INT_MAX;
	if (sign < 0)
		limit = (unsigned long)(-(INT_MIN + 1)) + 1UL;
	magnitude = 0;
	while (isdigit((unsigned char)*p))
	{
		unsigned long	digit = (unsigned long)(*p - '0');

		if (magnitude > (limit - digit) / 10UL)   /* inverse test: no overflow */
			return (-1);
		magnitude = magnitude * 10UL + digit;
		++p;
	}
	if (*p && !isspace((unsigned char)*p))
		return (-1);                               /* trailing garbage: 42abc  */
	if (sign < 0 && magnitude == limit)
		*out = INT_MIN;
	else if (sign < 0)
		*out = -(int)magnitude;
	else
		*out = (int)magnitude;
	*cursor = p;
	return (0);
}

static bool	has_duplicate(const t_stack *a, int value)
{
	size_t	i;

	for (i = 0; i < a->size; ++i)
		if (a->data[i] == value)
			return (true);
	return (false);
}

/* Count space-separated integers inside one operand token.               */
static size_t	count_in_token(const char *token)
{
	size_t	count = 0;

	while (*token)
	{
		while (*token && isspace((unsigned char)*token))
			++token;
		if (*token)
		{
			++count;
			while (*token && !isspace((unsigned char)*token))
				++token;
		}
	}
	return (count);
}

/* Fill one operand string (may contain several space-separated integers).  */
static int	fill_token(const char *token, t_stack *a)
{
	const char	*p = token;
	int			value;

	while (*p && isspace((unsigned char)*p))
		++p;
	if (!*p)
		return (-1);
	while (*p)
	{
		if (parse_integer(&p, &value) != 0)
			return (-1);
		if (has_duplicate(a, value))
			return (-1);
		a->data[a->size] = value;
		++a->size;
		while (*p && isspace((unsigned char)*p))
			++p;
	}
	return (0);
}

/* Decide whether an argv item is a flag or an operand.                     */
static bool	is_flag(const char *arg)
{
	if (arg[0] != '-' || arg[1] == '\0')
		return (false);
	if (arg[1] == '-')            /* "--" handled by caller as end-of-options */
		return (true);
	return (isalpha((unsigned char)arg[1]) != 0);
}

static int	apply_flag(const char *arg, t_strategy *forced, bool *bench)
{
	if (!strcmp(arg, "-s"))
		*forced = STRAT_SIMPLE;
	else if (!strcmp(arg, "-m"))
		*forced = STRAT_MEDIUM;
	else if (!strcmp(arg, "-c"))
		*forced = STRAT_COMPLEX;
	else if (!strcmp(arg, "-b"))
		*bench = true;
	else
		return (-1);
	return (0);
}

int	parse_input(int argc, char **argv, t_stacks *stacks,
		t_strategy *forced, bool *bench)
{
	size_t	capacity = 1;
	int		i;
	bool	options_enabled = true;

	*forced = STRAT_AUTO;
	*bench = false;
	/* Pass 0: count operand tokens so the ring buffer capacity is exact.   */
	i = 1;
	while (i < argc)
	{
		if (options_enabled && !strcmp(argv[i], "--"))
		{
			options_enabled = false;
			++i;
			continue;
		}
		if (options_enabled && is_flag(argv[i]))
		{
			if (apply_flag(argv[i], forced, bench) != 0)
				return (-1);
			++i;
			continue;
		}
		capacity += count_in_token(argv[i]);
		++i;
	}
	if (!init_stacks(stacks, capacity))
		return (-1);
	/* Pass 1: parse operands into stack A (head stays 0, linear fill).    */
	options_enabled = true;
	i = 1;
	while (i < argc)
	{
		if (options_enabled && !strcmp(argv[i], "--"))
		{
			options_enabled = false;
			++i;
			continue;
		}
		if (options_enabled && is_flag(argv[i]))
		{
			++i;
			continue;
		}
		if (fill_token(argv[i], &stacks->a) != 0)
		{
			free_stacks(stacks);
			return (-1);
		}
		++i;
	}
	if (stacks->a.size == 0)
	{
		free_stacks(stacks);
		return (-1);
	}
	return (0);
}

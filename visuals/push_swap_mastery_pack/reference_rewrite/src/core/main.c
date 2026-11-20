/* ************************************************************************** */
/*  src/core/main.c — entry point of the no-libft reference core            */
/*  Mirrors src/main.c of the real project: silent exit on no arguments,    */
/*  "Error\n" on stderr and exit code 1 on any parsing failure, full cleanup */
/*  on every path.                                                           */
/* ************************************************************************** */
#include "psw.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_stacks	stacks;
	t_stats		stats;
	t_strategy	forced;
	bool		bench;
	size_t		i;

	for (i = 0; i < OP_COUNT; ++i)
		stats.count[i] = 0;
	stats.total = 0;

	if (argc == 1)
		return (0);
	if (parse_input(argc, argv, &stacks, &forced, &bench) != 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	run_solver(&stacks, &stats, forced, bench);
	free_stacks(&stacks);
	return (0);
}

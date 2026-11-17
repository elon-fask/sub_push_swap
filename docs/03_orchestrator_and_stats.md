# Orchestrator, Disorder Metric & Benchmark Telemetry (`src/` & `src/stats/`)

This document explains the program orchestrator, the disorder ratio metric, the adaptive strategy dispatcher, and the benchmarking/telemetry system.

---

## 1. Program Main Flow (`src/main.c`)

```c
static int parse_input(int argc, char **argv, t_parse_result *result,
        t_context *context)
{
    if (parse_options(argc, argv, result) != 0)
        return (-1);
    if (parse_operands(&result->operands, &context->stacks) != 0)
    {
        destroy_parse_result(result);
        return (-1);
    }
    return (0);
}

static void run_program(t_context *context, t_parse_result *result)
{
    init_stats(&context->stats, &result->options);
    orchestrator(context, &result->options);
    if (result->options.benchmark_enabled)
        print_benchmark(&context->stats);
}

int main(int argc, char **argv)
{
    t_context       context;
    t_parse_result  result;

    if (argc == 1)
        return (0);
    if (parse_input(argc, argv, &result, &context) != 0)
    {
        ft_dprintf(STDERR_FILENO, "Error\n");
        return (1);
    }
    run_program(&context, &result);
    destroy_stacks(&context.stacks);
    destroy_parse_result(&result);
    return (0);
}
```

### Line Details & Standards Compliance:
1. `if (argc == 1) return (0);`: When no arguments are provided, push_swap must exit silently with code 0 (42 subject rule).
2. `parse_input()`: Parses options, then parses numbers into `context.stacks.a`.
3. If parsing fails: writes `"Error\n"` to `stderr` (`STDERR_FILENO`) using `ft_dprintf`, and exits with return code `1`.
4. `destroy_stacks(&context.stacks)` & `destroy_parse_result(&result)`: Guaranteed clean exit in all paths; zero memory leaks.

---

## 2. Orchestration & Early Exit (`src/orchestrator.c`)

```c
void orchestrator(t_context *context, const t_program_options *options)
{
    if (is_sorted(&context->stacks.a))
        return ;
    dispatch_strategy(context, options);
}
```

### Sorted Verification (`src/sorting/is_sorted.c`):
```c
bool is_sorted(const t_stack *stack)
{
    size_t i;
    int current;
    int next;

    i = 0;
    while (i + 1 < stack->size)
    {
        current = sorting_value_at(stack, i);
        next = sorting_value_at(stack, i + 1);
        if (current > next)
            return (false);
        ++i;
    }
    return (true);
}
```
- If the stack is already sorted, push_swap must output nothing and terminate immediately.
- `sorting_value_at(stack, i)` resolves the circular buffer offset to get the $i$-th element from the top.

---

## 3. Disorder Ratio: The Inversion Metric (`src/sorting/disorder_ratio.c`)

The disorder ratio is an normalized inversion metric based on Kendall's tau coefficient:

$$\text{Disorder Ratio} = \frac{\text{Number of Inverted Pairs}}{\text{Total Possible Pairs}} = \frac{\sum_{0 \le i < j < N} [A[i] > A[j]]}{\frac{N(N - 1)}{2}}$$

```c
double calculate_disorder_ratio(const t_stack *stack)
{
    size_t inversions;
    size_t total_pairs;
    size_t i;
    size_t j;

    inversions = 0;
    total_pairs = 0;
    i = 0;
    while (i < stack->size)
    {
        j = i + 1;
        while (j < stack->size)
        {
            ++total_pairs;
            if (stack->data[i] > stack->data[j])
                ++inversions;
            ++j;
        }
        ++i;
    }
    return ((double)inversions / total_pairs);
}
```

### Properties of the Disorder Ratio:
- $0.0$: Completely sorted array ($1, 2, 3, 4, 5$).
- $0.0 < \text{ratio} < 0.2$: Almost sorted array.
- $0.2 \le \text{ratio} < 0.5$: Moderately scrambled array.
- $0.5 \le \text{ratio} \le 1.0$: Highly disordered / reversed array ($1.0$ is completely reversed).

> [!NOTE]
> Notice that `disorder_ratio.c` accesses `stack->data[i]` directly without `sorting_value_at`. Since it runs initially when `head == 0` right after parsing, `stack->data[i]` corresponds to offset $i$. (See Code Review for suggested refinement with `sorting_value_at`).

---

## 4. Adaptive Strategy Dispatch (`src/orchestrator_dispatch.c`)

```c
static t_strategy select_adaptive_strategy(double disorder)
{
    if (disorder < 0.2)
        return (STRATEGY_SIMPLE);
    if (disorder < 0.5)
        return (STRATEGY_MEDIUM);
    return (STRATEGY_COMPLEX);
}

static void execute_strategy(t_context *context, t_strategy strategy)
{
    if (strategy == STRATEGY_SIMPLE)
        selection_sort(context);
    else if (strategy == STRATEGY_MEDIUM)
        chunk_sort(context);
    else if (strategy == STRATEGY_COMPLEX)
        turk_sort(context);
}

void dispatch_strategy(t_context *context, const t_program_options *options)
{
    t_strategy  strategy;
    double      disorder;

    strategy = options->strategy;
    if (options->strategy_explicit && strategy != STRATEGY_ADAPTIVE)
    {
        if (options->benchmark_enabled)
            record_disorder(context);
    }
    else if (strategy == STRATEGY_ADAPTIVE || options->benchmark_enabled)
    {
        disorder = record_disorder(context);
        if (strategy == STRATEGY_ADAPTIVE)
            strategy = select_adaptive_strategy(disorder);
    }
    stats_set_selected_strategy(&context->stats, strategy);
    execute_strategy(context, strategy);
}
```

### Why Adaptive Selection?
1. **Low Disorder ($< 0.2$)**: Selection sort or small tweaks require very few moves because most elements are already in order.
2. **Medium Disorder ($0.2 \le \text{ratio} < 0.5$)**: Chunk sort partitions the numbers into ranges, moving them efficiently with predictable bounds.
3. **High Disorder ($\ge 0.5$)**: Turk sort (greedy cost algorithm) computes the lowest synchronized cost (`rr`/`rrr`) for every node, producing top-tier performance for arbitrary/random permutations.

---

## 5. Telemetry & Benchmarking (`src/stats/`)

The stats module provides runtime metrics when running with `-b` or `--bench`.

### 5.1. `stats.h` & `stats.c`
Tracks each operation count independently:
```c
typedef enum e_operation
{
    OPERATION_SA,
    OPERATION_SB,
    OPERATION_SS,
    OPERATION_PA,
    OPERATION_PB,
    OPERATION_RA,
    OPERATION_RB,
    OPERATION_RR,
    OPERATION_RRA,
    OPERATION_RRB,
    OPERATION_RRR,
    OPERATION_COUNT
}   t_operation;
```
- `record_operation(stats, op)`: Increments the count for that operation in $O(1)$ time.

### 5.2. `print_benchmark.c`
Outputs to `stderr` (leaving `stdout` purely for instructions):
```
[bench] disorder: 64.20%
[bench] strategy: adaptive -> complex / O(n log n)
[bench] total ops: 684
[bench] sa: 12  sb: 0  ss: 0
[bench] pa: 97  pb: 97
[bench] ra: 145 rb: 132 rr: 68
[bench] rra: 54 rrb: 62 rrr: 17
```
This is invaluable for optimization, testing against the 42 subject move limits (e.g., $< 700$ for 100 numbers, $< 5500$ for 500 numbers).

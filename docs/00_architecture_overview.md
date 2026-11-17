# Architecture and High-Level Overview

## 1. Project Overview & Design Philosophy

This project is an advanced, production-grade implementation of the 42 / 1337 **`push_swap`** and **`checker`** projects.

Unlike conventional implementations that use singly or doubly linked lists, this implementation is architected around **cache-friendly circular dynamic ring buffers (`t_stack`)** allocated as flat contiguous arrays in memory. Every primitive push-swap operation (`push`, `pop`, `swap`, `rotate`, `reverse rotate`) executes in $O(1)$ constant time with zero dynamic allocations during the sorting routines.

Furthermore, it features an **adaptive algorithm orchestrator** that evaluates the **disorder ratio** (inversion metric) of the input numbers and selects the optimal sorting strategy:
1. **Small Sort** ($N \le 5$): Specialized minimal-move decision trees for 2, 3, 4, and 5 elements.
2. **Simple Strategy (Selection Sort)**: Minimal moves when elements are almost sorted or for tiny sets.
3. **Medium Strategy (Chunk Sort / Square-Root Decomposition)**: Heap-sort based ranking followed by windowed chunk partitioning.
4. **Complex Strategy (Turk Algorithm / Greedy Simultaneous Move)**: Complete cost matrix evaluation simulating simultaneous rotations (`rr`, `rrr`) to push and place elements at absolute minimal cost.

---

## 2. Core Data Structures

### `t_stack` (Circular Ring Buffer)
Located in [`src/stack/stack.h`](file:///home/harvesting/1337/1337/sync-btwn-cluster-and-lap/src/stack/stack.h):

```c
typedef struct s_stack
{
    int     *data;      /* Contiguous heap-allocated array */
    size_t  capacity;  /* Maximum elements stack can hold */
    size_t  head;      /* Array index of the TOP element */
    size_t  size;      /* Current number of active elements */
}   t_stack;
```

#### How the Circular Ring Buffer Works:
- **Top of Stack**: Always at `data[head]`.
- **Bottom of Stack**: Located at `data[(head + size - 1) % capacity]`.
- **Offset Access**: Element at depth $i$ from top ($0 \le i < \text{size}$) is at `data[(head + i) % capacity]`.
- **Push Top**: Pre-decrements `head` with wrap-around: `head = (head == 0) ? capacity - 1 : head - 1`, then writes `data[head] = val; size++`.
- **Pop Top**: Reads `val = data[head]`, then advances `head`: `head = (head + 1 == capacity) ? 0 : head + 1; size--`.
- **Rotate (`ra`/`rb`)**: Advances `head` by 1 and places the old top element at the new bottom. In fact, `head = (head + 1) % capacity; data[(head + size - 1) % capacity] = top_value;`.
- **Reverse Rotate (`rra`/`rrb`)**: Takes bottom element `data[(head + size - 1) % capacity]`, decrements `head` (with wrap), and writes it to `data[head]`.

This design completely avoids node allocation/freeing during sorting, prevents pointer chasing, and gives $O(1)$ performance with near-zero cache misses.

### `t_stacks`
```c
typedef struct s_stacks
{
    t_stack  a;
    t_stack  b;
}   t_stacks;
```

### `t_context`
Located in [`src/push_swap_internal.h`](file:///home/harvesting/1337/1337/sync-btwn-cluster-and-lap/src/push_swap_internal.h):
```c
typedef struct s_context
{
    t_stacks  stacks;
    t_stats   stats;
}   t_context;
```
Groups both stacks along with the telemetry/stats tracker into a unified context passed through execution phases.

### `t_program_options` & `t_parse_result`
Located in [`src/parsing/options/options.h`](file:///home/harvesting/1337/1337/sync-btwn-cluster-and-lap/src/parsing/options/options.h):
```c
typedef enum e_strategy
{
    STRATEGY_ADAPTIVE,  /* Automatically chosen based on disorder ratio */
    STRATEGY_SIMPLE,    /* Selection sort */
    STRATEGY_MEDIUM,    /* Chunk sort */
    STRATEGY_COMPLEX    /* Turk sort */
}   t_strategy;

typedef struct s_program_options
{
    t_strategy  strategy;
    bool        strategy_explicit;
    bool        benchmark_enabled;
}   t_program_options;
```

---

## 3. Directory Layout and File Dependency Graph

```
src/
├── main.c                          -> Program entrypoint & error exit
├── push_swap_internal.h            -> Internal orchestrator declarations & types
├── orchestrator.c                  -> High-level sorting trigger
├── orchestrator_dispatch.c         -> Disorder evaluation & strategy dispatch
├── stack/                          -> Primitive circular buffer stack operations
│   ├── stack.h
│   ├── initialize_stacks.c
│   ├── destroy_stacks.c
│   ├── stack_push_top.c
│   ├── stack_pop_top.c
│   ├── stack_swap_top.c
│   ├── stack_rotate.c
│   └── stack_reverse_rotate.c
├── operations/                     -> Operations that output to stdout & update stats
│   ├── operations.h
│   ├── operation_push.c            (pa, pb)
│   ├── operation_swap.c            (sa, sb, ss)
│   ├── operation_rotate.c          (ra, rb, rr)
│   └── operation_reverse_rotate.c  (rra, rrb, rrr)
├── parsing/                        -> Command line parsing & normalization
│   ├── parse_result.c
│   ├── operands/                   -> Value extraction, integer bounds, deduplication
│   │   ├── operands.h
│   │   ├── operands_internal.h
│   │   ├── count_operand_tokens.c
│   │   ├── parse_integer.c
│   │   ├── parse_operand.c
│   │   └── parse_operands.c
│   └── options/                    -> Flag handling (-a, -s, -m, -c, -b, --bench, etc.)
│       ├── options.h
│       ├── options_internal.h
│       ├── apply_option.c
│       ├── parse_long_option.c
│       ├── parse_options.c
│       ├── parse_short_options.c
│       └── scan_arguments.c
├── stats/                          -> Telemetry, benchmarks & metrics
│   ├── stats.h
│   ├── stats.c
│   └── print_benchmark.c
├── sorting/                        -> Algorithms
│   ├── is_sorted.c                 -> Verification check
│   ├── disorder_ratio.c            -> Inversion count calculation
│   ├── disorder_ratio.h
│   ├── utils/                      -> Helpers: index resolution, distances, rotation
│   │   ├── sorting_utils.h
│   │   ├── stack_lookup.c
│   │   ├── rotation_distance.c
│   │   └── rotate_to_offset.c
│   ├── small_sort/                 -> Hardcoded optimal sorts for size <= 5
│   │   ├── small_sort.h
│   │   ├── small_sort_internal.h
│   │   ├── small_sort.c
│   │   ├── small_sort_utils.c      (sort_two)
│   │   ├── sort_three.c
│   │   └── sort_five.c
│   ├── selection/                  -> O(N^2) Selection Sort
│   │   ├── selection_sort.h
│   │   └── selection_sort.c
│   ├── chunk/                      -> O(N sqrt(N)) Chunk Sort
│   │   ├── chunk.h
│   │   ├── chunk_internal.h
│   │   ├── chunk_sort.c
│   │   ├── chunk_index.c           (In-place heap sort ranking)
│   │   ├── chunk_partition.c       (Window push to B with rb optimization)
│   │   └── chunk_restore.c         (Greedy pop back from B to A)
│   └── turk/                       -> O(N log N) Turk / Greedy Simultaneous Cost Sort
│       ├── turk.h
│       ├── turk_internal.h
│       ├── turk_sort.c
│       ├── turk_cost.c             (Cost evaluation loop)
│       ├── turk_cost_utils.c       (Cost computation & rotation wrappers)
│       ├── turk_target_a.c         (Target slot lookup in A for B element)
│       ├── turk_target_b.c         (Target slot lookup in B for A element)
│       ├── turk_move.c             (Synchronized rotation execution)
│       ├── turk_small_sort.c       (Base-3 sort in A)
│       └── turk_finalize.c         (Final rotation to put min element at top)
└── bonus/                          -> Checker bonus program
    ├── checker_internal_bonus.h
    ├── main_bonus.c
    ├── checker_dispatch_bonus.c
    ├── checker_loop_bonus.c
    ├── execute_push_bonus.c
    ├── execute_swap_bonus.c
    ├── execute_rotate_bonus.c
    └── execute_reverse_rotate_bonus.c
```

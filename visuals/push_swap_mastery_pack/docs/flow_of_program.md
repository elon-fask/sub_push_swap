# Program Flow — `push_swap` (grounded in the actual source)

> Companion to the visual guide `push_swap_study_guide.html`. Every function below
> comes from the repository `elon-fask/sub_push_swap`. Read this after the
> architecture diagram in the HTML, or use it as a defense walkthrough script.

## 1. High-level call graph

```
main(int argc, char **argv)                         src/main.c
├── if (argc == 1) return (0);                      subject: silent exit
├── parse_input()                                   src/main.c (static)
│   ├── parse_options(argc, argv, &result)          src/parsing/options/parse_options.c
│   │   ├── initialize_parse_result(argc, result)   options_internal.c
│   │   └── run_parser → scan_arguments()           scan_arguments.c
│   │         ├── classify_argument()                static
│   │         ├── store_operand()                    static
│   │         ├── parse_short_options()             parse_short_options.c
│   │         ├── parse_long_option()                parse_long_option.c
│   │         └── apply_option() → set_strategy()   apply_option.c
│   └── parse_operands(&result.operands, &stacks)   src/parsing/operands/parse_operands.c
│         ├── count_operand_tokens()                count_operand_tokens.c
│         ├── initialize_stacks(&stacks, count)     src/stack/initialize_stacks.c
│         └── per token → parse_operand()           parse_operand.c
│               ├── parse_integer()                 parse_integer.c
│               │   ├── parse_sign() (static)
│               │   └── parse_magnitude() (static, overflow inverse test)
│               ├── contains_value() duplicate scan   (static)
│               └── stack_push_top() → data[size]    src/stack/stack_push_top.c
├── run_program()                                   src/main.c (static)
│   ├── init_stats(&stats, &options)                src/stats/stats.c
│   ├── orchestrator(context, &options)              src/orchestrator.c
│   │   ├── if is_sorted(&a) return;               sorting/is_sorted.c
│   │   └── dispatch_strategy(context, &options)   src/orchestrator_dispatch.c
│   │         ├── record_disorder(context)          static → disorder_ratio.c
│   │         ├── select_adaptive_strategy(d)       static (thresholds)
│   │         ├── stats_set_selected_strategy()     stats.c
│   │         └── execute_strategy(strategy)        static
│   │               ├── selection_sort()            sorting/selection/selection_sort.c
│   │               ├── chunk_sort()                sorting/chunk/chunk_sort.c
│   │               └── turk_sort()                sorting/turk/turk_sort.c
│   └── if (benchmark_enabled) print_benchmark()    stats/print_benchmark.c (stderr)
├── destroy_stacks(&stacks)                         stack/destroy_stacks.c
└── destroy_parse_result(&result)                   parsing/parse_result.c
```

The bonus binary `checker` (`src/bonus/main_bonus.c`) shares parsing and stack
primitives, replaces the solver with an instruction loop, and prints `OK` / `KO`.

## 2. Step-by-step execution trace

| Stage | Function(s) executed | What happens | Failure behavior |
|---|---|---|---|
| 0. No args | `main` | `argc == 1` → `return (0)`, no output | exit code 0 |
| 1. Option parsing | `parse_options` | Reads flags (`-s -m -c -b` / `--simple --medium --complex --bench`); operands collected into `result.operands` | unknown flag → `Error`, exit 1 |
| 2. Token counting | `count_operand_tokens` | Splits every operand string on spaces; total = ring capacity | 0 tokens → `Error` |
| 3. Allocation | `initialize_stacks` | Allocates A and B rings of `count` `int`s; `head=0,size=0` | alloc failure → `Error` |
| 4. Number parsing | `parse_operand` → `parse_integer` | Sign, magnitude with inverse overflow test, duplicate scan, append at `data[size]` | non-digit / overflow / duplicate → `Error`, exit 1 |
| 5. Stats init | `init_stats` | Zeroes 11 counters; records requested strategy & bench flag | — |
| 6. Sorted check | `is_sorted` | Scans offsets 0..size-1 on A; ascending → solver skipped | exit 0, no output |
| 7. Disorder | `record_disorder` → `calculate_disorder_ratio` | Counts inversions; ratio = inversions / N(N-1)/2 | — |
| 8. Strategy select | `select_adaptive_strategy` | `<0.2` simple; `<0.5` medium; else complex; explicit flag overrides | — |
| 9. Solve | `execute_strategy` | Small sets (≤5) route into `small_sort`; large sets run the chosen algorithm; every emitted instruction goes through an `operation_*` wrapper that prints and records | — |
| 10. Benchmark | `print_benchmark` | Writes ratio, strategy, total + per-op counts to **stderr** (stdout stays pure instructions) | — |
| 11. Cleanup | `destroy_stacks`, `destroy_parse_result` | Frees both rings + operand array; zero leaks | — |

## 3. The three decision points a defender must be able to explain

1. **Why two parsers?** Options (`parse_options`) consume argv tokens that begin
   with `-` and leave everything else in `result.operands`; integers
   (`parse_operands`) then split those strings on whitespace and validate them.
2. **Why measure disorder before sorting?** `dispatch_strategy` only chooses a
   solver when `STRATEGY_ADAPTIVE` (or bench mode); an explicit `-s/-m/-c` flag
   bypasses selection but still records the ratio when bench is on.
3. **Where do instructions come from?** No solver prints directly; every move
   calls `operation_*` (operations/), which invokes the stack primitive, prints
   the mnemonic on stdout, and increments a stats counter. This keeps the
   checker bonus (which calls primitives without printing) on the same core.

## 4. Data flow of one instruction (example: `pb`)

```
selection_sort / chunk_sort / turk_sort
        │  call
        ▼
operation_pb(stacks, stats)                     operations/operation_push.c
        │  pop_top(&stacks->a, &value)
        ▼
stack_pop_top(&a, &value)                       stack/stack_pop_top.c
        │  reads data[head]; head = (head+1) % cap; --size
        ▼
stack_push_top(&b, value)                       stack/stack_push_top.c
        │  head = (head-1+cap) % cap; data[head]=value; ++size
        ▼
write "pb\n" to stdout; record(OP_PB)
```

## 5. Ring-buffer invariants (memorize these)

- `capacity` = number of valid integers (both rings share it).
- `head` = physical index of the **top**; logical offset `k` = physical
  `(head + k) % capacity` (`sorting_index_at` / `sorting_value_at`).
- Push: `head -= 1 (mod cap)`, write, `size += 1`. Pop: read `data[head]`,
  `head += 1 (mod cap)`, `size -= 1`.
- `rotate` (`ra/rb`): top value saved, head advanced, value rewritten at the new
  bottom `(head + size - 1) % capacity` — data moves with the head.
- `reverse_rotate` (`rra/rrb`): bottom saved, head backed up, bottom value
  rewritten at the new head.
- `swap_top`: swaps `data[head]` with `data[(head+1)%capacity]`; head unchanged.

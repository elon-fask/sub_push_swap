# Function Reference — every file and every function in the project

Legend: **Sig** = signature as compiled; **Role** = one line; **Calls** = main
callees; **Callers** = who invokes it. Static functions are marked `(static)`.
Source tree root: `src/`.

## A. Core entry & orchestration

### `main.c`
| Function | Signature | Role | Calls | Callers |
|---|---|---|---|---|
| `main` | `int main(int argc, char **argv)` | Silent exit on no args; parse; run; cleanup | `parse_input`, `run_program`, `destroy_stacks`, `destroy_parse_result` | runtime |
| `parse_input` (static) | `static int parse_input(int, char**, t_parse_result*, t_context*)` | Run options then operands parser | `parse_options`, `parse_operands`, `destroy_parse_result` | `main` |
| `run_program` (static) | `static void run_program(t_context*, t_parse_result*)` | Init stats, run orchestrator, print benchmark if on | `init_stats`, `orchestrator`, `print_benchmark` | `main` |

### `orchestrator.c`
| Function | Signature | Role | Calls | Callers |
|---|---|---|---|---|
| `orchestrator` | `void orchestrator(t_context*, const t_program_options*)` | Early exit if sorted; otherwise dispatch | `is_sorted`, `dispatch_strategy` | `run_program` |

### `orchestrator_dispatch.c`
| Function | Signature | Role | Calls | Callers |
|---|---|---|---|---|
| `dispatch_strategy` | `void dispatch_strategy(t_context*, const t_program_options*)` | Record disorder; honor explicit flag; adaptive selection; execute | `record_disorder`, `select_adaptive_strategy`, `stats_set_selected_strategy`, `execute_strategy` | `orchestrator` |
| `record_disorder` (static) | `static double record_disorder(t_context*)` | Compute ratio and store in stats | `calculate_disorder_ratio`, `stats_set_disorder_ratio` | `dispatch_strategy` |
| `select_adaptive_strategy` (static) | `static t_strategy select_adaptive_strategy(double)` | `<0.2` SIMPLE, `<0.5` MEDIUM, else COMPLEX | — | `dispatch_strategy` |
| `execute_strategy` (static) | `static void execute_strategy(t_context*, t_strategy)` | Map enum to solver | `selection_sort`, `chunk_sort`, `turk_sort` | `dispatch_strategy` |

## B. Stack layer (`stack/`) — ring buffer

| File / Function | Signature | Role | Calls | Callers |
|---|---|---|---|---|
| `initialize_stacks.c` | `int initialize_stacks(t_stacks*, size_t capacity)` | Allocate both rings; zero head/size | `ft_calloc` | `parse_operands` |
| `destroy_stacks.c` | `void destroy_stacks(t_stacks*)` | Free both rings; null pointers | `free` | `main`, bonus `main_bonus` |
| `stack_push_top.c` | `t_stack_status stack_push_top(t_stack*, int)` | Back head modulo cap; write; `size++`; `CHANGED`/`UNCHANGED` | — | operation wrappers, parser |
| `stack_pop_top.c` | `t_stack_status stack_pop_top(t_stack*, int*)` | Read `data[head]`; advance head; `size--` | — | operation push wrappers, checker `transfer_top` |
| `stack_swap_top.c` | `t_stack_status stack_swap_top(t_stack*)` | Swap top two logical slots if `size>=2` | — | swap wrappers, checker |
| `stack_rotate.c` | `t_stack_status stack_rotate(t_stack*)` | Save top; advance head; copy value to new bottom | — | rotate wrappers, checker |
| `stack_reverse_rotate.c` | `t_stack_status stack_reverse_rotate(t_stack*)` | Save bottom; back head; copy value to new head | — | reverse-rotate wrappers, checker |

`stack.h` defines `t_stack { int *data; size_t capacity, head, size; }`,
`t_stacks { t_stack a, b; }`, and `t_stack_status { STACK_UNCHANGED, STACK_CHANGED }`.

## C. Operations layer (`operations/`) — print + record

All wrappers: call primitive; on `STACK_CHANGED` print the mnemonic with
`ft_printf("%s\n", name)` and `record_operation(stats, OP_*)`. Combined ops
(`ss`, `rr`, `rrr`) fire if at least one primitive changed.

| Function | File | Wraps | Emits |
|---|---|---|---|
| `operation_pa` / `operation_pb` | `operation_push.c` | pop B→push A / pop A→push B | `pa` / `pb` |
| `operation_sa` / `operation_sb` | `operation_swap.c` | `stack_swap_top` on A / B | `sa` / `sb` |
| `operation_ss` | `operation_swap.c` | both swaps | `ss` |
| `operation_ra` / `operation_rb` | `operation_rotate.c` | `stack_rotate` | `ra` / `rb` |
| `operation_rr` | `operation_rotate.c` | both rotates | `rr` |
| `operation_rra` / `operation_rrb` | `operation_reverse_rotate.c` | `stack_reverse_rotate` | `rra` / `rrb` |
| `operation_rrr` | `operation_reverse_rotate.c` | both reverse rotates | `rrr` |

## D. Parsing layer

### Options (`parsing/options/`)
| Function | Signature | Role |
|---|---|---|
| `parse_options` | `int parse_options(int, char**, t_parse_result*)` | Initialize result; run parser; return status |
| `initialize_parse_result` | `int initialize_parse_result(int, t_parse_result*)` | Zero options; build empty operand list |
| `destroy_parse_result` | `void destroy_parse_result(t_parse_result*)` | Free operand values array |
| `scan_arguments` | `static int scan_arguments(t_parse_context*)` | Loop argv: classify → flag or store |
| `process_argument` / `classify_argument` / `store_operand` | static helpers | Route `-x`, `--long`, plain strings |
| `parse_short_options` | `int parse_short_options(t_parse_context*, char*)` | Cluster parsing (`-b -c`, `-bc` style registry) |
| `parse_long_option` | `int parse_long_option(t_parse_context*, char*)` | `--simple/--medium/--complex/--bench`; `--` ends options |
| `find_short_option` / `find_long_option` | static | Look up registry entries |
| `apply_option` | `int apply_option(t_parse_context*, const t_option_spec*)` | Set flag; `set_strategy` for strategy flags |

Registry (`options_internal.h`): short/long strings mapped to `OPTION_STRATEGY_*`
or `OPTION_BENCH` actions.

### Operands (`parsing/operands/`)
| Function | Signature | Role | Calls |
|---|---|---|---|
| `parse_operands` | `int parse_operands(const t_operands*, t_stacks*)` | Count tokens; init stacks; parse each token | `count_operand_tokens`, `initialize_stacks`, `parse_operand` |
| `parse_operand` | `static int parse_operand(const char*, t_stack*)` | Skip spaces; parse integer; duplicate check; append | `parse_integer`, `contains_value`, `stack_push_top` |
| `parse_integer` | `int parse_integer(const char**, int*)` | Sign + magnitude; returns `-1` on error | `parse_sign`, `parse_magnitude` (static) |
| `parse_magnitude` (static) | `static int parse_magnitude(const char**, unsigned long, unsigned long*)` | Per-digit inverse overflow test `magnitude > (limit - digit)/10` | — |
| `contains_value` (static) | `static bool contains_value(const t_stack*, int)` | Linear duplicate scan over filled prefix | — |
| `count_operand_tokens` | `size_t count_operand_tokens(const t_operands*)` | Total space-separated integers | `count_argument_tokens` (static) |

## E. Stats layer (`stats/`)

| Function | Role |
|---|---|
| `init_stats(t_stats*, const t_program_options*)` | Zero 11 counters; store requested strategy and bench flag |
| `record_operation(t_stats*, t_operation)` | Increment one counter and total |
| `stats_set_selected_strategy` / `stats_set_disorder_ratio` | Record dispatcher choice and ratio |
| `print_benchmark(const t_stats*)` | stderr report: ratio %, strategy label, total ops, per-op groups |

`stats.h` defines the 11-value `t_operation` enum.

## F. Sorting layer (`sorting/`)

### Metrics & lookups
| Function | File | Role |
|---|---|---|
| `calculate_disorder_ratio` | `disorder_ratio.c` | Inversions / total pairs (O(N²)) |
| `is_sorted` | `is_sorted.c` | Ascending scan with `sorting_value_at` |
| `sorting_index_at` / `sorting_value_at` | `utils/stack_lookup.c` | Logical offset → physical `(head+offset)%capacity` |
| `sorting_minimum_offset` / `sorting_maximum_offset` | `utils/stack_lookup.c` | `find_extreme_offset` scan; return logical offset |
| `sorting_rotation_distance` | `utils/rotation_distance.c` | `offset` forward; `size-offset` reverse |
| `sorting_rotate_to_offset` | `utils/rotate_to_offset.c` | Pick shorter direction; `rotate_steps` fires `ra/rra` or `rb/rrb` |

### Small sort (`small_sort/`) — used for N ≤ 5
| Function | Role |
|---|---|
| `small_sort` | Router by stack size |
| `sort_two` | `sa` only if `v0 > v1` |
| `sort_three` | Max to bottom via `ra` (max@0) / `rra` (max@1); `sa` if top two inverted |
| `sort_five` | Repeatedly push minimum to B; `sort_three`; push B back (`pa`) |

### Selection (`selection/selection_sort.c`)
| Function | Role |
|---|---|
| `selection_sort` | N≤5 → `small_sort`; else push every minimum A→B, then `pa` all back |

### Chunk (`chunk/`) — medium disorder
| Function | File | Role |
|---|---|---|
| `chunk_sort` | `chunk_sort.c` | Orchestrate rank → partition → restore; fallback to `turk_sort` on alloc failure |
| `chunk_rank_values` / `chunk_restore_values` | `chunk_index.c` | Heapsort items; overwrite A with ranks; restore originals at end |
| `sort_chunk_items` / `sift_chunk_heap` / `swap_chunk_items` | `chunk_index.c` | Static heapsort helpers |
| `chunk_calculate_width` | `chunk_partition.c` | `root` = smallest k with k² > n; `width = 2*(root-1)` |
| `chunk_partition` | `chunk_partition.c` | Walk rank ranges; `chunk_process_range` moves matches A→B |
| `chunk_process_range` | `chunk_partition.c` | `pb` matches; `rb` lower-half ranks; `ra` to scan |
| `chunk_push_back` | `chunk_restore.c` | Pop B maxima to A until B empty |

### Turk (`turk/`) — high disorder
| Function | File | Role |
|---|---|---|
| `turk_sort` | `turk_sort.c` | Loop cheapest A→B until 3 left; `turk_sort_small`; loop cheapest B→A; final min rotation |
| `turk_sort_small` | `turk_small_sort.c` | Internal 3-sort; 2-sort descending; 1 no-op |
| `turk_find_cheapest_move` | `turk_cost.c` | Scan source; evaluate 4 direction combos; keep min cost |
| `turk_calculate_rotation_cost` | `turk_cost.c` | Same direction → `max`; different → `sum` |
| `consider_directions` / `turk_evaluate_forward` / `turk_evaluate_reverse` / `turk_update_move` | `turk_cost.c` | Static cost evaluation helpers |
| `turk_target_in_b` / `find_predecessor` | `turk_target_b.c` | Predecessor (largest smaller); fallback = B maximum |
| `turk_target_in_a` / `find_successor` | `turk_target_a.c` | Successor (smallest larger); fallback = A minimum |
| `turk_execute_move` | `turk_move.c` | Shared `rr`/`rrr`, source remainder, target remainder, push |
| `rotate_shared` / `rotate_remaining_source` / `rotate_remaining_target` / `push_move` | `turk_move.c` | Static execution stages |
| `turk_rotate_minimum_to_top` | `turk_finalize.c` | Shortest-path rotation so minimum sits at offset 0 |

## G. Bonus checker (`bonus/`)

| Function | Role |
|---|---|
| `main_bonus` | Parse operands; run instruction loop; `OK` if `is_sorted(a) && b.size==0` else `KO`; cleanup |
| `process_instructions` | `get_next_line` loop; invalid line → cleanup + error |
| `execute_instruction` | First-char dispatch (`s/p/r` + `r?`) |
| `execute_push` (+`transfer_top`) | `pa` / `pb`; empty stack = silent no-op |
| `execute_swap` / `execute_rotate` / `execute_reverse_rotate` | Call primitives directly; no print, no stats |

## H. Key data structures (with defining header)

| Type | Header | Fields |
|---|---|---|
| `t_stack` | `stack/stack.h` | `int *data; size_t capacity, head, size;` |
| `t_stacks` | same | `t_stack a, b;` |
| `t_stack_status` | same | `UNCHANGED = 0, CHANGED = 1` |
| `t_program_options` | `parsing/options/options.h` | `t_strategy strategy; bool strategy_explicit, benchmark_enabled;` |
| `t_operands` | `parsing/operands/operands.h` | `char **values; size_t count, capacity;` |
| `t_parse_result` | `parsing/parse_result.c`/internal | `t_program_options options; t_operands operands;` |
| `t_stats` | `stats/stats.h` | requested/selected strategy, disorder ratio, `count[OPERATION_COUNT]` |
| `t_context` | `push_swap_internal.h` | `t_stacks stacks; t_stats stats;` |
| `t_chunk_item` / `t_chunk_state` | `chunk/chunk_internal.h` | value + physical index; items array + size + context |
| `t_turk_move` | `turk/turk_internal.h` | source/target index, both rotation counts, total cost, direction flags, source_is_a |

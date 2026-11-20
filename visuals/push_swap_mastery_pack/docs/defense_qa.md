# Defense Q&A — model answers grounded in this codebase

Answers reflect the actual source (not a generic push_swap). Numbers are
measured; see `algorithm_traces.md`.

## Core design

**Q1. Why a circular array (`t_stack`) instead of a doubly linked list?**
Single `malloc` per ring; push/pop/swap/rotate are O(1) index math modulo
`capacity`; contiguous `int` array gives cache locality; no per-node allocations
(≈24 bytes/node + fragmentation) and no pointer chasing. Capacity equals the
input integer count, allocated once in `initialize_stacks`.

**Q2. How do `ra` / `rra` work without shifting array elements?**
- `ra` (`stack_rotate`): save the top value, advance `head`, write that value
  into the new bottom slot `(head + size - 1) % capacity`.
- `rra` (`stack_reverse_rotate`): read the bottom value, back `head` up, write
  the value at the new `head`.
One value copy per rotate; the head pointer does most of the work; O(1).

**Q3. `sa` when the stack has one element?**
`stack_swap_top` returns `STACK_UNCHANGED` for `size < 2`; the wrapper then
prints nothing and records nothing — invalid/no-op operations are never emitted.

**Q4. What does the header `push_swap_internal.h` gather?**
Shared context: `t_context { t_stacks stacks; t_stats stats; }`, the strategy
enum, operation enum, and public cross-module prototypes. `internal` = shared
within the program; external interfaces live in `stack.h`, `stats.h`, etc.

## Parsing

**Q5. How is integer overflow prevented?**
`parse_magnitude` checks `if (magnitude > (limit - digit) / 10UL) return -1;`
**before** multiplying. `limit` = `INT_MAX` for positives; for negatives it is
`(unsigned long)(-(INT_MIN + 1)) + 1UL`, which accepts exactly `-2147483648`.
A trailing non-digit (e.g. `12a`) fails; `+`/`-` without digits fail; empty or
whitespace-only tokens fail.

**Q6. Where are duplicates detected?**
`contains_value` scans the already-filled prefix `data[0..size)` during
`parse_operand`, before `stack_push_top`. Duplicate → cleanup + `Error\n` (stderr),
exit 1.

**Q7. Why two parsing passes/modules?**
`parse_options` scans argv for flags (`-s -m -c -b`, `--long`, `--`) and stores
plain tokens in `result.operands`; `parse_operands` then counts space-separated
tokens (exact capacity), allocates stacks, and validates each integer. This
keeps flag syntax independent of number syntax and supports quoted multi-number
arguments (`"3 2 1"`).

## Metrics & dispatch

**Q8. Define the disorder ratio and the thresholds.**
`inversions / C(N,2)`, O(N²) pairwise count. `< 0.2` → selection (simple),
`< 0.5` → chunk (medium), `≥ 0.5` → turk (complex). Measured demo ratio:
39.39 % → medium. An explicit `-s/-m/-c` overrides selection; bench mode records
the ratio even for forced strategies; `is_sorted` short-circuits before any solver.

**Q9. What are the complexities of the three solvers?**
Selection O(N²) rotations; chunk O(N√N) heapsort + √N-wide partitions; turk
O(N²) cost scans per element but with shared rotations in practice yielding
~550–650 ops for N=100 and ~5.2k–5.8k for N=500.

## Algorithms

**Q10. Walk through `sort_three`.**
Find maximum offset: max at 0 → `ra`; max at 1 → `rra`; max at 2 stays. Then,
if top > second, `sa`. At most 2 moves.

**Q11. How does chunk sort avoid overflow-sensitive raw values?**
It compresses values to ranks 0..N−1 with an in-place heapsort
(`sort_chunk_items` + `sift_chunk_heap`), partitions rank ranges, and restores
original values from `items[rank].value` before finishing. Width = 2(√n-ish):
smallest k with k²>n, width = 2(k−1). Lower-half ranks get `rb` after `pb` to
pre-sort B; restore repeatedly pops B's maximum.

**Q12. Turk: what target does an A element seek in B?**
B is kept circular **descending**; target = predecessor = largest value smaller
than v; if none, land above B's maximum. On the way back B→A, A is circular
**ascending**; target = successor = smallest value larger than v; if none, land
above A's minimum.

**Q13. Turk cost evaluation.**
For a candidate: forward = offset, reverse = size−offset. Same direction pairs
share `rr`/`rrr` → cost `max(a,b)`; opposite directions → `a+b`. All four pairs
evaluated; global minimum over the source stack chosen; execution order: shared
rotations, source leftovers, target leftovers, push.

**Q14. Why does turk stop at 3 elements in A?**
The remainder is sorted by the minimal `turk_sort_small` (theoretical 3-element
optimum) while all larger decisions were already cost-optimized; then B returns
to its successor slots and the minimum is rotated to top.

## Operations & bonus

**Q15. Difference between `rr` and `ra`+`rb`?** `rr` emits one shared mnemonic
while rotating both rings; checker executes both primitives. Real N=100 runs
show ~68 `rr` + ~50 `rrr` — sharing is a major part of Turk's low move count.

**Q16. Checker flow.** `main_bonus` parses the same operands, reads stdin lines
with `get_next_line`, dispatches by first character (`s/p/r`), runs primitives
directly (no printing, no stats), and prints `OK` iff A is sorted and B empty,
else `KO`; invalid instruction → `Error\n` exit 1. Empty-stack pushes are silent
no-ops.

## Engineering & robustness

**Q17. Memory management.** Allocations: two ring arrays (`initialize_stacks`),
the operand values array, chunk `items` array (`ft_calloc`, freed on all paths
including the turk fallback). Frees: `destroy_stacks`, `destroy_parse_result`,
`free` of chunk state; checker frees stacks and GNL static buffers on error.

**Q18. What are the bench flags for?** `-b/--bench` writes a per-operation count
and chosen strategy to **stderr**, leaving stdout pure instructions; used to
tune against 42 move limits. Flags are extras — the solver output never contains
bench text when piped to the checker.

**Q19. Known weak points to preempt.** (a) Selection sort is O(N²) and only
selected at low disorder or small N. (b) `calculate_disorder_ratio` reads
`data[i]` directly; valid because it runs before any mutation (head = 0); a
defensive version would use `sorting_value_at`. (c) On chunk allocation failure
the code falls back to `turk_sort` rather than failing. (d) N=500 random runs
occasionally exceed 5500 ops while staying under the ~8500 passing threshold.

**Q20. How would you rebuild it (no libft)?** See `rewrite_plan_no_libft.md` and
the compilable `reference_rewrite/` core: `write()` replaces `ft_printf`,
`strcmp/isspace/isdigit/strlen/calloc` replace the libft equivalents, and the
same ring-buffer design and solver order are preserved.

# Rewrite Plan — rebuild the project without libft

Goal: understand every module deeply enough to retype it from scratch during
evaluation. The folder `reference_rewrite/` contains a **compilable teaching
core** (no libft) covering phases 1–4; advanced solvers ship as annotated stubs.

## 1. Libft → libc replacement table (audited from the source)

| Real call (count) | Replacement | Notes |
|---|---|---|
| `ft_printf("pb\n", …)` (×20) | `write(1, "pb\n", 3)` | operation wrappers only; mnemonic lengths known |
| `ft_dprintf(STDERR_FILENO, "Error\n")` (×11) | `write(2, "Error\n", 6)` | benchmark numbers need a small `itoa` writer |
| `ft_strcmp` (×13) | `strcmp` (`<string.h>`) | option names, checker instruction names |
| `ft_isspace` (×5) | `isspace((unsigned char)c)` (`<ctype.h>`) | token scanning |
| `ft_isdigit` (×3) | `isdigit((unsigned char)c)` | integer parser |
| `ft_isalpha` (×1) | `isalpha((unsigned char)c)` | flag classification |
| `ft_strlen` (×1) | `strlen` | checker newline trim |
| `ft_calloc` (×1) | `calloc(count, size)` | chunk items; zeroing matters |
| `get_next_line(fd)` | local `read_line(fd, &line)` | checker bonus only; `read` + grow buffer |

Everything else (ring buffer, sorting) already uses only stdlib.

## 2. Build order (6 phases, each independently testable)

### Phase 1 — Ring buffer (`src/stack/`)
Files: `initialize_stacks.c`, `destroy_stacks.c`, `stack_push_top.c`,
`stack_pop_top.c`, `stack_swap_top.c`, `stack_rotate.c`,
`stack_reverse_rotate.c`, `stack.h`.
Acceptance: unit driver pushing/popping, rotate and reverse-rotate preserve
cyclic order; empty `pop` returns `UNCHANGED`.
Core delivered: `reference_rewrite/src/stack/stack.c`.

### Phase 2 — Operation wrappers (`src/operations/`)
Files: push, swap, rotate, reverse-rotate + headers.
Acceptance: each wrapper prints the exact mnemonic only when the primitive
changed; `ss/rr/rrr` print once if either side changed; stats counter increments.
Core delivered: `reference_rewrite/src/operations/ops.c`.

### Phase 3 — Parser (`src/parsing/`)
Files: options layer, operands layer (`parse_integer` with inverse overflow
test, duplicate scan, quoted/whitespace tokens).
Acceptance (gate):
```
./prog            -> silent exit 0
./prog 2 1        -> valid instructions; ./checker OK
./prog 2 2        -> Error, exit 1
./prog 2147483648 -> Error, exit 1
./prog -2147483648 2147483647 -> OK
./prog "3 2 1"    -> OK
```
Core delivered: `reference_rewrite/src/parsing/parse.c`.

### Phase 4 — Small sort + selection (`src/sorting/`)
Files: `utils/` lookups and `rotate_to_offset`; `small_sort/` (2, 3, 5);
`selection/selection_sort.c`; `is_sorted.c`; `disorder_ratio.c`.
Acceptance: `3 2 1` → `ra sa`; `5 4 3 2 1` ≤ 12 ops; sorted input silent.
Core delivered: `reference_rewrite/src/sorting/sort.c`.

### Phase 5 — Advanced solvers (annotated stubs provided)
- Chunk: `chunk_stub.c` — ranks (heapsort), width `2(k−1)`, partition with
  lower-half `rb`, maximum-first restore, value restore.
- Turk: `turk_stub.c` — predecessor/successor targets, 4-combo cost, shared
  rotation execution, 3-element tail, final minimum rotation.
Gate: N=100 under 700 ops; N=500 under 8500 ops; checker `OK` on every run.

### Phase 6 — Bonus checker (`src/bonus/`)
Files: GNL loop, dispatch, four executor groups; `OK` / `KO` / `Error`.
Gate: `./push_swap $ARG | ./checker $ARG` → `OK`; feed a bogus instruction →
`Error`; feed unsorted output → `KO`.

## 3. Keeping the architecture faithful while simplifying

| Real project | Teaching core | Why |
|---|---|---||
| 11 `operation_*` files | one `ops.c` | same call sequence, easier to read |
| Options registry + long flags | short flags only | parser behavior identical for numbers |
| Full chunk + turk | documented stubs | core compiles fast; advanced logic studied from stubs |
| ft_printf formatting | `write` mnemonics | stdout bytes identical (`pa\n` etc.) |
| Stats + benchmark module | one `print_bench` helper | demonstration of stderr reporting |

## 4. Rebuild workflow checklist

1. Write `t_stack`/`t_stacks` first; do not touch sorting until pop/push behave.
2. Print through wrappers only — solvers must never call `write` directly.
3. Validate parser before any solver; invalid input must never reach the stack.
4. Implement `is_sorted` and `small_sort` before `selection_sort`.
5. Add chunk, then turk; compare measured op counts against `algorithm_traces.md`.
6. Finish the checker last; reuse primitives — no duplicate stack logic.

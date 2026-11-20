# Algorithm Traces & Measured Evidence

All numbers below were measured from the compiled project
(`make && make bonus`), not estimated. Demo input used throughout:

```
ARG="7 2 9 1 4 11 8 3 12 5 10 6"      # 12 distinct integers
```

## 1. Measured results on the 12-element demo

Disorder ratio measured: **39.39 %** (26 inversions out of 66 pairs → adaptive
dispatch selects **medium (chunk)**).

| Command | Strategy | Total ops | Verifier | Measured breakdown |
|---|---|---:|---|---|
| `./push_swap $ARG` | adaptive → medium | **41** | `OK` | pa 12, pb 12, ra 6, rb 6, rrb 5 |
| `./push_swap -s $ARG` | simple (selection) | **45** | `OK` | pa 12, pb 12, ra 13, rra 8 |
| `./push_swap -m $ARG` | medium (chunk) | **41** | `OK` | pa 12, pb 12, ra 6, rb 6, rrb 5 |
| `./push_swap -c $ARG` | complex (turk) | **34** | `OK` | pa 9, pb 9, sa 1, ra 3, rb 3, rra 5, rrb 3, rrr 1 |

Observation for the defense: on this medium-disorder permutation Turk still
wins (34 ops); the dispatcher optimizes for typical large-random inputs where
chunk's `O(n√n)` beats selection and avoids Turk's constant overhead for small N.

## 2. Small sort (N ≤ 5) — real stdout

`./push_swap 3 2 1`:
```
ra
sa
```
(Max 3 is at top → `ra` sends it to bottom; top two inverted → `sa`.)

`./push_swap 5 4 3 2 1`:
```
rra
pb
rra
pb
ra
sa
pa
pa
```
Two minima moved to B, three sorted with `ra sa`, B pushed back.

## 3. Selection sort (`-s`, 45 ops) — mechanics

Loop until A empty: find minimum offset, shortest-path rotate to top, `pb`;
then `pa` until B empty. Measured rotation budget on the demo: `ra 13`, `rra 8`,
`pb 12`, `pa 12`. O(N²) rotations — used only below 0.2 disorder or as the N≤5
fallback.

## 4. Chunk sort (`-m`, 41 ops) — mechanics on the demo

Ranks for the demo (value → rank):

| value | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| rank | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |

Width: `root` = smallest k with k² > 12 → 4; `width = 2 × (4 − 1) = 6`.
Ranges: `[0,6)` then `[6,12)`. Inside a range, lower-half ranks
(`rank < start + width/2`) receive an `rb` after `pb`, sinking them deep in B.
Restore pops the B **maximum** repeatedly; descending pops leave A ascending.

Measured: `pb 12`, `ra 6` (scanning A), `rb 6` + `rrb 5` (B arrangement),
`pa 12`.

## 5. Turk sort (`-c`, 34 ops) — cost model (illustrative state)

State: B top→bottom = `[8, 5, 3, 1]` (circular descending). Candidate v = 6
sits at A offset 2 (A size 5 → forward 2, reverse 3). Predecessor of 6 in B is
5, at B offset 1 (forward 1, reverse 3).

| Direction pair | Shared? | Cost formula | Cost |
|---|---|---|---:|
| A fwd (`ra`) + B fwd (`rb`) | share `rr` | max(2, 1) | **2** |
| A rev (`rra`) + B rev (`rrb`) | share `rrr` | max(3, 3) | 3 |
| A fwd + B rev | none | 2 + 3 | 5 |
| A rev + B fwd | none | 3 + 1 | 4 |

Cheapest = both forward, cost 2: `rr` once, `ra` once, then `pb`. The real
`s_turk_move` stores `source_reverse` / `target_reverse` so execution emits
`rr`/`rrr` first, leftovers second, push last.

Phase summary on the demo: 9 elements A→B with cheapest moves; 3 sorted in A;
9 moved B→A with successor targets; minimum rotated to top. Measured shared
rotations: `rrr 1`; singles dominate at this size.

## 6. Large random benchmarks (measured, `shuf` permutations)

| Size | Runs | Observed ops | 42 guideline |
|---|---|---|---|
| 100 | 5 | 542, 549, 571, 648, 652 | full score ≲ 700 |
| 500 | 3 | 5191, 5745, 5756 | full score ≲ 5500; pass ≲ 8500 |

Representative N=100 Turk breakdown (one run, total 591):
`pb 97, pa 97, ra 98, rb 59, rr 68, rra 34, rrb 87, rrr 50, sa 1` —
118 shared rotations (`rr`+`rrr`) are the win over separate rotations.

## 7. Edge cases (expected behavior)

| Input | Expected |
|---|---|
| (no args) | silent, exit 0 |
| `1 2 3 4 5` | silent, exit 0 (already sorted) |
| `42` | silent, exit 0 |
| `1 2 3 2` | `Error\n` on stderr, exit 1 (duplicate) |
| `2147483648` / `-2147483649` | `Error\n`, exit 1 (overflow/underflow) |
| `2147483647 -2147483648` | sorts correctly (limits valid) |
| `""` / `"   "` | `Error\n`, exit 1 |
| `+` / `-` | `Error\n`, exit 1 |
| `"3 2 1"` (one quoted string) | sorts correctly |
| `"1 5 2" 4 "3"` (mixed) | sorts correctly |
| `abc` / `12a` | `Error\n`, exit 1 |

Checker verification pattern:
```
./push_swap $ARG | ./checker $ARG      # prints OK or KO
./push_swap $ARG | wc -l               # instruction count
```

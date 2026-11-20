# Push_swap Mastery Pack

A study-and-rebuild kit for the `sub_push_swap` project (42 / 1337 push_swap),
prepared for the peer evaluation. Every explanation and number in this pack
was derived from the actual source repository and from measurements taken on
the compiled binaries.

## Contents

| Path | What it is |
|---|---|
| `push_swap_study_guide.html` | **Main visual guide**: architecture diagrams, program flow, stack mechanics, all four solvers with visuals, measured data, function index, defense Q&A, rewrite roadmap. Open in any browser (no server, no internet needed). |
| `docs/flow_of_program.md` | End-to-end call graph and stage-by-stage execution trace. |
| `docs/function_reference.md` | Every file, every function: signature, role, callees, callers, data structures. |
| `docs/algorithm_traces.md` | Measured traces: 12-element demo per strategy, small-sort outputs, Turk cost example, N=100/N=500 benchmarks, edge cases. |
| `docs/defense_qa.md` | 20 model defense answers grounded in this codebase. |
| `docs/rewrite_plan_no_libft.md` | From-scratch rebuild roadmap; libft → libc replacement table; six phases with acceptance gates. |
| `docs/testing_checklist.md` | Checker-based test commands and expected outputs. |
| `reference_rewrite/` | Compilable no-libft teaching core (`make` → `psw_core`) mirroring the real architecture, plus annotated chunk/Turk stubs. |
| `tests/run_tests.sh` | Edge-case smoke tests for the teaching core. |

## Suggested study order

1. Open `push_swap_study_guide.html` → sections **Overview → Flow → Architecture**.
2. Study **Stack primitives** and **Operations** until the ring-buffer diagram
   is memorized; cross-read `docs/flow_of_program.md`.
3. Walk **Disorder metric** and the four solvers in order; compare `docs/algorithm_traces.md`.
4. Go through **Function reference** top to bottom (`docs/function_reference.md`).
5. Rehearse `docs/defense_qa.md` out loud.
6. Rebuild with `docs/rewrite_plan_no_libft.md` against `reference_rewrite/`,
   running `tests/run_tests.sh` after each phase.

## Measured reference numbers (compiled from the real repo)

- Demo `7 2 9 1 4 11 8 3 12 5 10 6`, disorder 39.39 %:
  adaptive 41 ops (chunk), selection 45, chunk 41, turk 34; all checker `OK`.
- N=100 random: 542–652 ops; N=500 random: 5191–5756 ops.
- `3 2 1` → `ra sa`; invalid input → `Error\n`, exit 1; sorted/empty input → silent, exit 0.

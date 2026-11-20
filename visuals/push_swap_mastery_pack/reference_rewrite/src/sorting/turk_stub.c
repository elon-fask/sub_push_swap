/* ************************************************************************** */
/*  turk_stub.c — ANNOTATED REFERENCE ONLY, not compiled into psw_core.     */
/*  Corresponds to the teammate's src/sorting/turk/ module (10 files).       */
/*  Greedy cheapest-move algorithm; the defense's centerpiece.               */
/* ************************************************************************** */

/*
 * DATA (turk_internal.h)
 * ------------------------------------------------------------------
 * typedef struct s_turk_move {
 *     size_t source_index;      // logical offset of the element to move
 *     size_t target_index;      // logical offset of its landing slot
 *     size_t source_rotations;
 *     size_t target_rotations;
 *     size_t total_cost;        // after 4-way direction evaluation
 *     bool   source_is_a;
 *     bool   source_reverse;    // move A (or B) backwards with rra / rrb
 *     bool   target_reverse;
 * } t_turk_move;
 *
 * MAIN LOOP (turk_sort.c: turk_sort)
 * ------------------------------------------------------------------
 *  1. while (a.size > 3):
 *       turk_find_cheapest_move(a.size, &a, &b, source_is_a = true, &best);
 *       turk_execute_move(context, &best);          // shared rotations, then pb
 *  2. turk_sort_small(context);                       // sort the remaining 3 in A
 *  3. while (b.size > 0):
 *       turk_find_cheapest_move(b.size, &b, &a, source_is_a = false, &best);
 *       turk_execute_move(context, &best);          // ... then pa
 *  4. turk_rotate_minimum_to_top(context);            // ra/rra so min sits on top
 *
 * TARGET POSITIONS
 * ------------------------------------------------------------------
 * Target in B (turk_target_b.c): B stays circular DESCENDING.
 *   Find predecessor = largest value strictly smaller than v.
 *   If none exists (v new max or new min): land above B's MAXIMUM.
 * Target in A (turk_target_a.c): A stays circular ASCENDING.
 *   Find successor = smallest value strictly larger than v.
 *   If none exists (v largest): land above A's MINIMUM.
 *
 * ROTATION DISTANCES
 * ------------------------------------------------------------------
 *   forward steps = offset;   reverse steps = size - offset.
 *
 * COST MODEL (turk_cost.c: turk_calculate_rotation_cost) — 4 direction combos
 * ------------------------------------------------------------------
 *  (fwd A, fwd B)   -> share rr : cost = max(src, tgt)
 *  (rev A, rev B)   -> share rrr: cost = max(src, tgt)
 *  (fwd A, rev B)   -> separate : cost = src + tgt
 *  (rev A, fwd B)   -> separate : cost = src + tgt
 * consider_directions evaluates all four for one candidate; turk_find_cheapest_move
 * scans every element of the source stack and keeps the global minimum total_cost.
 *
 * EXECUTION (turk_move.c: turk_execute_move)
 * ------------------------------------------------------------------
 *  1. rotate_shared:  while both remaining > 0 and same direction -> rr / rrr
 *  2. rotate_remaining_source: leftover ra/rra (or rb/rrb)
 *  3. rotate_remaining_target: leftover rb/rrb (or ra/rra)
 *  4. push_move: pb when source_is_a, otherwise pa.
 *
 * SMALL TAIL (turk_small_sort.c: turk_sort_small)
 * ------------------------------------------------------------------
 *  a.size == 3 -> internal sort_three (max to bottom, then sa if needed).
 *  a.size == 2 -> sort_descending (sa if out of descending order).
 *  a.size == 1 -> sort_middle_value (no-op).
 *
 * FINALIZE (turk_finalize.c)
 * ------------------------------------------------------------------
 *  offset = sorting_minimum_offset(&a);
 *  sorting_rotate_to_offset(&a, offset, forward_on_tie = true);
 */

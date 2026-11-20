/* ************************************************************************** */
/*  chunk_stub.c — ANNOTATED REFERENCE ONLY, not compiled into psw_core.     */
/*  Corresponds to the teammate's src/sorting/chunk/ module:                  */
/*    chunk_sort.c, chunk_index.c, chunk_partition.c, chunk_restore.c       */
/*  Target complexity O(n sqrt n). Read this file top to bottom before you  */
/*  rewrite chunk_sort from scratch.                                         */
/* ************************************************************************** */

/*
 * STEP 0 — API
 * ------------------------------------------------------------------
 * void chunk_sort(t_context *context);
 *
 * Local state:
 *   typedef struct s_chunk_item { int value; size_t physical_index; } t_chunk_item;
 *   typedef struct s_chunk_state {
 *       t_context     *context;
 *       t_chunk_item  *items;   // ft_calloc(size, sizeof(t_chunk_item))
 *       size_t        size;
 *   } t_chunk_state;
 * On calloc failure the real code falls back to turk_sort(context).
 *
 * STEP 1 — Rank compression (chunk_index.c: chunk_rank_values)
 * ------------------------------------------------------------------
 * 1. Fill items[i] = { .value = data[(head+i)%cap], .physical_index = (head+i)%cap }
 * 2. Heapsort items ascending by value (sort_chunk_items + sift_chunk_heap;
 *    in-place, O(n log n), no recursion).
 * 3. Overwrite stack A with ranks:
 *      a->data[items[i].physical_index] = (int)i;     // rank i (0 = smallest)
 *    Raw values are kept in items[rank].value for the final restore.
 *
 * STEP 2 — Chunk width (chunk_partition.c: chunk_calculate_width)
 * ------------------------------------------------------------------
 *   root = 1; while (root <= size / root) ++root;   // smallest k with k*k > n
 *   width = (root - 1) * 2;                          // ≈ 2 * sqrt(n)
 *   n=100 -> width 20 (~5 chunks); n=500 -> width 44 (~11 chunks).
 *
 * STEP 3 — Partition A -> B, chunk after chunk (chunk_partition.c)
 * ------------------------------------------------------------------
 *   for (start = 0; start < size; start += width):
 *       end = min(start + width, size);
 *       remaining = end - start;
 *       while (remaining > 0):
 *           rank = value_at(a, 0);
 *           if (start <= rank < end):
 *               pb();
 *               if (rank < start + (end - start) / 2):   // lower half
 *                   rb();                                // sink it in B
 *               remaining--;
 *           else:
 *               ra();                                      // scan to next match
 *   Optimization: lower-half ranks get an rb after pb so B ends up with
 *   small values deep and large values near top, cutting restore rotations.
 *
 * STEP 4 — Restore B -> A in descending order (chunk_restore.c)
 * ------------------------------------------------------------------
 *   while (b.size > 0):
 *       off = max_offset(b);
 *       rotate_to_offset(b, off);      // shortest path ra/rb-style (rb/rrb)
 *       pa();
 *   Popping maxima first leaves A ascending top -> bottom.
 *
 * STEP 5 — Restore original values (chunk_index.c: chunk_restore_values)
 * ------------------------------------------------------------------
 *   rank = data[physical_index]; data[physical_index] = items[rank].value;
 *   Free items. Stack A holds the original integers, sorted.
 */

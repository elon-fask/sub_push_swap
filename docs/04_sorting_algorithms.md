# Sorting Algorithms & Mathematical Foundations (`src/sorting/`)

This document is the core study manual for the push_swap sorting algorithms. It details every mathematical concept, data flow, helper function, and algorithm implemented in the project.

---

## 1. Foundation: Sorting Utilities (`src/sorting/utils/`)

Before understanding any algorithm, you must master the index and rotation abstraction helpers.

### 1.1. Physical vs. Logical Indexing (`stack_lookup.c`)

In a circular ring buffer, the top element is at index `head`. The element at logical offset `offset` from the top is at:

$$\text{physical\_index} = (\text{head} + \text{offset}) \pmod{\text{capacity}}$$

```c
size_t sorting_index_at(const t_stack *stack, size_t offset)
{
    return ((stack->head + offset) % stack->capacity);
}

int sorting_value_at(const t_stack *stack, size_t offset)
{
    return (stack->data[sorting_index_at(stack, offset)]);
}
```

#### Finding Extremes (`sorting_minimum_offset` & `sorting_maximum_offset`):
```c
static size_t find_extreme_offset(const t_stack *stack, bool minimum)
{
    size_t  i;
    size_t  best_offset;
    int     best;
    int     current;

    best_offset = 0;
    best = sorting_value_at(stack, 0);
    i = 1;
    while (i < stack->size)
    {
        current = sorting_value_at(stack, i);
        if ((minimum && current < best) || (!minimum && current > best))
        {
            best = current;
            best_offset = i;
        }
        ++i;
    }
    return (best_offset);
}
```
Scans all elements from logical offset $0$ to $size - 1$ and returns the logical offset of the minimum or maximum element.

---

### 1.2. Rotation Distance & Direction (`rotation_distance.c`)

To bring an element at logical offset `offset` to the top (offset $0$):
- **Forward Rotation (`ra` / `rb`)**: Requires `offset` steps.
- **Reverse Rotation (`rra` / `rrb`)**: Requires `size - offset` steps.

```c
size_t sorting_rotation_distance(size_t size, size_t offset, bool reverse)
{
    if (reverse)
        return (size - offset);
    return (offset);
}
```

---

### 1.3. Bringing Any Offset to Top (`rotate_to_offset.c`)

```c
void sorting_rotate_to_offset(t_context *context, t_stack *stack,
        size_t target_offset, bool forward_on_tie)
{
    size_t  forward_steps;
    size_t  reverse_steps;

    forward_steps = sorting_rotation_distance(stack->size, target_offset, false);
    reverse_steps = sorting_rotation_distance(stack->size, target_offset, true);
    if (forward_steps < reverse_steps
        || (forward_on_tie && forward_steps == reverse_steps))
        rotate_steps(context, stack, forward_steps, false);
    else
        rotate_steps(context, stack, reverse_steps, true);
}
```
Compares `forward_steps` vs. `reverse_steps` and executes the minimum of the two.

---

## 2. Small Sort Engine: $N \le 5$ (`src/sorting/small_sort/`)

All general sorting algorithms delegate sets of size $\le 5$ to `small_sort()` to guarantee minimal instructions.

### 2.1. Sorting 2 Elements (`small_sort_utils.c`)
```c
void sort_two(t_context *context)
{
    int first = sorting_value_at(&context->stacks.a, 0);
    int second = sorting_value_at(&context->stacks.a, 1);
    if (first > second)
        operation_sa(&context->stacks.a, &context->stats);
}
```
If first > second, a single `sa` sorts the stack. Cost: $\le 1$ move.

### 2.2. Sorting 3 Elements (`sort_three.c`)
There are $3! = 6$ possible permutations of 3 numbers. One is already sorted. The remaining 5 permutations are solved in at most 2 moves:

```c
void sort_three(t_context *context)
{
    size_t  maximum_offset;
    t_stack *stack;

    stack = &context->stacks.a;
    maximum_offset = sorting_maximum_offset(stack);
    if (maximum_offset == 0)
        operation_ra(stack, &context->stats);
    else if (maximum_offset == 1)
        operation_rra(stack, &context->stats);
    if (sorting_value_at(stack, 0) > sorting_value_at(stack, 1))
        operation_sa(stack, &context->stats);
}
```

#### Decision Matrix Analysis:
1. **Find where the maximum element is**:
   - If maximum is at index 0 (top): `ra` moves it to the bottom.
   - If maximum is at index 1 (middle): `rra` moves the bottom element to the top, which displaces the maximum to the bottom.
   - If maximum is at index 2 (bottom): It's already in the correct place!
2. **After step 1, the maximum is guaranteed to be at the bottom!**
3. Now only elements at indices 0 and 1 remain. If `val[0] > val[1]`, a single `sa` completes the sort!
Total moves: **At most 2 moves** (maximum possible efficiency for 3 elements).

### 2.3. Sorting 4 and 5 Elements (`sort_five.c`)
```c
static void move_minimum_to_b(t_context *context)
{
    size_t minimum_offset = sorting_minimum_offset(&context->stacks.a);
    sorting_rotate_to_offset(context, &context->stacks.a, minimum_offset, false);
    operation_pb(&context->stacks, &context->stats);
}

void sort_five(t_context *context)
{
    while (context->stacks.a.size > 3)
        move_minimum_to_b(context);
    sort_three(context);
    while (context->stacks.b.size > 0)
        operation_pa(&context->stacks, &context->stats);
}
```
1. Finds the minimum element in A and rotates it to the top via the shortest path (`ra` or `rra`).
2. Pushes it to B (`pb`).
3. If $N = 5$, repeats for the second minimum element.
4. When exactly 3 elements remain in A, sorts them with `sort_three()` in $\le 2$ moves.
5. Pushes elements back from B to A (`pa`). Because the smallest elements were pushed in ascending order, pushing them back automatically places them at the top in sorted order.
Total moves: **At most 12 moves** for 5 elements (well within 42's 12-move limit).

---

## 3. Simple Strategy: Selection Sort (`src/sorting/selection/`)

Complexity: $O(N^2)$ moves.

```c
void selection_sort(t_context *context)
{
    if (context->stacks.a.size <= 5)
    {
        small_sort(context);
        return ;
    }
    while (context->stacks.a.size > 0)
    {
        sorting_rotate_to_offset(context, &context->stacks.a,
            sorting_minimum_offset(&context->stacks.a), false);
        operation_pb(&context->stacks, &context->stats);
    }
    while (context->stacks.b.size > 0)
        operation_pa(&context->stacks, &context->stats);
}
```
- Repeatedly finds the minimum element of A, rotates it to top, and pushes to B.
- When A is empty, pushes all elements back from B to A.
- Ideal when disorder ratio is very low ($< 0.2$), meaning elements are almost in place.

---

## 4. Medium Strategy: Chunk Sort (`src/sorting/chunk/`)

Chunk sort is an $O(N \sqrt{N})$ algorithm inspired by square-root decomposition and window-based bucket sorting.

### 4.1. Step 1: In-Place Coordinate Compression / Ranking (`chunk_index.c`)
To partition elements without value distortion, raw values (which could be anywhere in the range `[INT_MIN, INT_MAX]`) are ranked from $0$ to $N - 1$.

```c
typedef struct s_chunk_item
{
    int     value;
    size_t  physical_index;
}   t_chunk_item;
```

1. Copies every element and its original physical index into a temporary array `state->items`.
2. Sorts `state->items` in ascending order using **Heapsort** (`sort_chunk_items` and `sift_chunk_heap`):
   - Guaranteed $O(N \log N)$ worst-case time with zero recursion.
3. Overwrites each element in stack A with its **rank** (its index $0 \le \text{rank} < N$ in the sorted array):
   `a->data[state->items[i].physical_index] = (int)i;`
4. The values are later restored perfectly to their original numbers in `chunk_restore_values()` using `state->items[rank].value`!

### 4.2. Step 2: Dynamic Chunk Width Calculation (`chunk_partition.c`)
```c
void chunk_calculate_width(size_t *width, size_t size)
{
    size_t root = 1;
    while (root <= size / root)
        ++root;
    *width = (root - 1) * 2;
}
```
Calculates $\lfloor \sqrt{N} \rfloor \times 2$.
- For 100 elements: $\sqrt{100} = 10 \implies \text{width} = 20$ (approx. 5 chunks).
- For 500 elements: $\sqrt{500} \approx 22 \implies \text{width} = 44$ (approx. 11 chunks).

### 4.3. Step 3: Partitioning with Median Bifurcation (`chunk_process_range`)
```c
void chunk_process_range(t_chunk_state *state)
{
    t_context   *context = state->context;
    size_t      remaining = state->end - state->start;
    int         rank;

    while (remaining > 0)
    {
        rank = sorting_value_at(&context->stacks.a, 0);
        if ((size_t)rank >= state->start && (size_t)rank < state->end)
        {
            operation_pb(&context->stacks, &context->stats);
            if ((size_t)rank < state->start + (state->end - state->start) / 2)
                operation_rb(&context->stacks.b, &context->stats);
            --remaining;
        }
        else
            operation_ra(&context->stacks.a, &context->stats);
    }
}
```

#### The Secret Optimization:
When an element in range `[start, end)` is found:
- Push to B (`pb`).
- **If the rank is in the lower half of the chunk** (`rank < start + width / 2`), immediately execute `rb`!
- This places smaller items in the bottom half of B and larger items in the top half of B!
- When later pushing back, the stack B is already roughly ordered as an hourglass / circle, drastically reducing retrieval rotations!

### 4.4. Step 4: Restoring from B to A (`chunk_restore.c`)
```c
void chunk_push_back(t_chunk_state *state)
{
    t_context   *context = state->context;
    size_t      maximum_offset;

    while (context->stacks.b.size > 0)
    {
        maximum_offset = sorting_maximum_offset(&context->stacks.b);
        sorting_rotate_to_offset(context, &context->stacks.b, maximum_offset, false);
        operation_pa(&context->stacks, &context->stats);
    }
}
```
Repeatedly finds the maximum element in B, rotates it to top via the shortest path, and pushes it back to A. Since elements are pushed in descending order, Stack A ends up completely sorted!

---

## 5. Complex Strategy: The Turk Sort Algorithm (`src/sorting/turk/`)

Turk Sort is an advanced greedy optimization algorithm that yields outstanding move counts ($< 600$ for 100 numbers, $< 5000$ for 500 numbers).

### 5.1. The Principle of Turk Sort
Instead of pushing blindly or sorting sequentially:
1. Pushes elements from A to B while maintaining stack B in **circular descending order**.
2. For *every single element* in A, it calculates:
   - Where it would land in B (target index).
   - How many rotations A needs.
   - How many rotations B needs.
   - How many rotations can be **combined** using `rr` (both forward) or `rrr` (both reverse).
3. Selects the element with the **absolute lowest total cost across the entire stack**, executes the synchronized rotation, and pushes.
4. Stops when only 3 elements remain in A, sorts those 3 with `turk_sort_small()`.
5. Greedily pushes everything back from B into its correct position in A.
6. Finally, rotates A so the minimum element is at the top.

---

### 5.2. Calculating Target Positions

#### Target in B for an element from A (`turk_target_b.c`):
B must be sorted in circular descending order.
For value $V$:
- We want to place $V$ above the **largest value smaller than $V$** (its predecessor).
- If $V$ is smaller than everything in B, or larger than everything in B, it should be placed above the **maximum value in B**.

```c
static bool find_predecessor(const t_stack *stack, int value, size_t *target)
{
    bool    found = false;
    int     best;
    int     current;
    size_t  i = 0;

    while (i < stack->size)
    {
        current = sorting_value_at(stack, i);
        if (current < value && (!found || current > best))
        {
            best = current;
            *target = i;
            found = true;
        }
        ++i;
    }
    return (found);
}

void turk_target_in_b(size_t *target, int value, const t_stack *b)
{
    if (b->size == 0)
    {
        *target = 0;
        return ;
    }
    if (!find_predecessor(b, value, target))
        *target = sorting_maximum_offset(b);
}
```

#### Target in A for an element from B (`turk_target_a.c`):
When pushing back from B to A, A must be in circular ascending order.
For value $V$:
- We want to place $V$ above the **smallest value larger than $V$** (its successor).
- If no successor exists ($V$ is larger than all elements in A), place it above the **minimum value in A**.

```c
static bool find_successor(const t_stack *stack, int value, size_t *target)
{
    bool    found = false;
    int     best;
    int     current;
    size_t  i = 0;

    while (i < stack->size)
    {
        current = sorting_value_at(stack, i);
        if (current > value && (!found || current < best))
        {
            best = current;
            *target = i;
            found = true;
        }
        ++i;
    }
    return (found);
}

void turk_target_in_a(size_t *target, int value, const t_stack *a)
{
    if (!find_successor(a, value, target))
        *target = sorting_minimum_offset(a);
}
```

---

### 5.3. Cost Calculation & 4-Way Direction Evaluation (`turk_cost.c` & `turk_cost_utils.c`)

Each stack can rotate in 2 directions: Forward (`ra`/`rb`) or Reverse (`rra`/`rrb`).
Between Stack A and Stack B, there are $2 \times 2 = 4$ direction combinations:
1. **Both Forward (`ra` and `rb`)**: Can share `rr` operations!
   $$\text{Cost} = \max(\text{rotations}_A, \text{rotations}_B)$$
2. **Both Reverse (`rra` and `rrb`)**: Can share `rrr` operations!
   $$\text{Cost} = \max(\text{rotations}_A, \text{rotations}_B)$$
3. **Opposite (`ra` and `rrb`)**: Cannot share operations.
   $$\text{Cost} = \text{rotations}_A + \text{rotations}_B$$
4. **Opposite (`rra` and `rb`)**: Cannot share operations.
   $$\text{Cost} = \text{rotations}_A + \text{rotations}_B$$

```c
void turk_calculate_rotation_cost(t_turk_move *move)
{
    if (move->source_reverse != move->target_reverse)
        move->total_cost = move->source_rotations + move->target_rotations;
    else if (move->source_rotations > move->target_rotations)
        move->total_cost = move->source_rotations;
    else
        move->total_cost = move->target_rotations;
}
```

`turk_find_cheapest_move()` loops through every index in `source`, checks all 4 direction pairs via `consider_directions()`, and preserves the global cheapest move across the entire stack!

---

### 5.4. Synchronized Move Execution (`turk_move.c`)

Once the optimal candidate is found:
```c
void turk_execute_move(t_context *context, const t_turk_move *move)
{
    size_t  source_rotations = move->source_rotations;
    size_t  target_rotations = move->target_rotations;

    rotate_shared(context, move, &source_rotations, &target_rotations);
    rotate_remaining_source(context, move, source_rotations);
    rotate_remaining_target(context, move, target_rotations);
    push_move(context, move);
}
```
1. **`rotate_shared`**: While both `source_rotations > 0` and `target_rotations > 0` with identical direction, issues `rr` or `rrr`.
2. **`rotate_remaining_source`**: Issues individual `ra` / `rra` for the leftover rotations.
3. **`rotate_remaining_target`**: Issues individual `rb` / `rrb` for the leftover rotations.
4. **`push_move`**: Issues `pb` (if source is A) or `pa` (if source is B).

---

### 5.5. Finalizing (`turk_finalize.c`)
```c
void turk_rotate_minimum_to_top(t_context *context)
{
    size_t offset = sorting_minimum_offset(&context->stacks.a);
    sorting_rotate_to_offset(context, &context->stacks.a, offset, true);
}
```
After all elements are pushed back into A in circular sorted order, the minimum element might not be at index 0. A final rotation (`ra` or `rra`) rotates the minimum to the top of A. Stack A is now completely sorted!

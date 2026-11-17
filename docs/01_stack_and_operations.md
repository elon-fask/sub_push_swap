# Stack Implementation & Operations (`src/stack/` & `src/operations/`)

This document provides a line-by-line and architectural breakdown of the stack memory model and push-swap primitive operations.

---

## 1. Stack Data Structure (`src/stack/stack.h`)

```c
typedef struct s_stack
{
    int     *data;      // Heap-allocated dynamic integer array
    size_t  capacity;  // Total buffer capacity (equals total numbers parsed)
    size_t  head;      // Index in data[] representing the TOP of the stack
    size_t  size;      // Number of valid elements currently in the stack
}   t_stack;

typedef struct s_stacks
{
    t_stack a;
    t_stack b;
}   t_stacks;

typedef enum e_stack_status
{
    STACK_UNCHANGED,
    STACK_CHANGED
}   t_stack_status;
```

### Why Circular Ring Buffer over Linked List?
- **Space Efficiency**: An integer list node requires `sizeof(int) + sizeof(struct s_node *) = 16 bytes` on 64-bit systems due to padding. A contiguous buffer requires only 4 bytes per integer.
- **Cache Locality**: Elements are contiguous in memory; accessing neighbors incurs L1/L2 cache hits rather than random pointer dereferences.
- **Constant Time**: Every operation (`push`, `pop`, `swap`, `rotate`, `reverse rotate`) executes in $O(1)$ operations purely by manipulating the `head` pointer and array indices. Zero `malloc`/`free` calls during sorting.

---

## 2. Detailed Line-by-Line Breakdown: `src/stack/`

### 2.1. `initialize_stacks.c`

```c
int initialize_stacks(t_stacks *stacks, size_t capacity)
{
    *stacks = (t_stacks){0};
    if (capacity > SIZE_MAX / sizeof(*stacks->a.data))
        return (-1);
    stacks->a.data = malloc(capacity * sizeof(*stacks->a.data));
    if (!stacks->a.data)
        return (-1);
    stacks->b.data = malloc(capacity * sizeof(*stacks->b.data));
    if (!stacks->b.data)
    {
        free(stacks->a.data);
        stacks->a.data = NULL;
        return (-1);
    }
    stacks->a.head = 0;
    stacks->a.size = 0;
    stacks->a.capacity = capacity;
    stacks->b.head = 0;
    stacks->b.size = 0;
    stacks->b.capacity = capacity;
    return (0);
}
```

#### Line Details:
- **`*stacks = (t_stacks){0};`**: Zero-initializes all structure fields safely.
- **`if (capacity > SIZE_MAX / sizeof(*stacks->a.data))`**: Multiplication overflow check before calling malloc. Prevents integer wrap-around vulnerabilities on huge capacity values.
- **`stacks->a.data = malloc(...)`**: Allocates the array buffer for stack A.
- **`if (!stacks->a.data) return (-1);`**: Handles allocation failure.
- **`stacks->b.data = malloc(...)`**: Allocates the array buffer for stack B.
- **`if (!stacks->b.data)` block**: If B fails, A is cleaned up immediately to avoid memory leaks, setting `stacks->a.data = NULL`.
- **`head = 0`, `size = 0`, `capacity = capacity`**: Configures both stacks as empty buffers with capacity up to all input elements.

---

### 2.2. `destroy_stacks.c`

```c
void destroy_stacks(t_stacks *stacks)
{
    free(stacks->a.data);
    free(stacks->b.data);
    stacks->a.data = NULL;
    stacks->b.data = NULL;
    stacks->a.head = 0;
    stacks->b.head = 0;
    stacks->a.size = 0;
    stacks->b.size = 0;
    stacks->a.capacity = 0;
    stacks->b.capacity = 0;
}
```

#### Line Details:
- Frees `stacks->a.data` and `stacks->b.data`.
- Nulls the pointers to prevent dangling pointer bugs or double-free issues.
- Resets sizes, heads, and capacities to zero.

---

### 2.3. `stack_push_top.c`

```c
t_stack_status stack_push_top(t_stack *stack, int new_value)
{
    if (stack->size == stack->capacity)
        return (STACK_UNCHANGED);
    if (stack->head == 0)
        stack->head = stack->capacity - 1;
    else
        --stack->head;
    stack->data[stack->head] = new_value;
    ++stack->size;
    return (STACK_CHANGED);
}
```

#### Explanation & Logic:
- **Pushing onto top of stack** in a ring buffer means moving the top boundary backwards (counter-clockwise).
- If `head == 0`, wrapping occurs to `capacity - 1`. Otherwise, `head` is decremented.
- `stack->data[stack->head] = new_value` places the new value at the new top index.
- Increments `stack->size` and returns `STACK_CHANGED`.
- If the stack is full (`size == capacity`), returns `STACK_UNCHANGED` safely.

---

### 2.4. `stack_pop_top.c`

```c
t_stack_status stack_pop_top(t_stack *stack, int *popped_value)
{
    if (stack->size == 0)
        return (STACK_UNCHANGED);
    *popped_value = stack->data[stack->head];
    ++stack->head;
    if (stack->head == stack->capacity)
        stack->head = 0;
    --stack->size;
    return (STACK_CHANGED);
}
```

#### Explanation & Logic:
- Checks if `size == 0`. If empty, returns `STACK_UNCHANGED`.
- Copies `stack->data[stack->head]` into `*popped_value`.
- Advances `head` forward (clockwise). If `head == capacity`, wraps back to `0`.
- Decrements `size` and returns `STACK_CHANGED`.

---

### 2.5. `stack_swap_top.c`

```c
t_stack_status stack_swap_top(t_stack *stack)
{
    size_t  second;
    int     temp;

    if (stack->size < 2)
        return (STACK_UNCHANGED);
    second = stack->head + 1;
    if (second == stack->capacity)
        second = 0;
    temp = stack->data[stack->head];
    stack->data[stack->head] = stack->data[second];
    stack->data[second] = temp;
    return (STACK_CHANGED);
}
```

#### Explanation & Logic:
- Swaps the top element (`head`) with the second element from top (`(head + 1) % capacity`).
- If `stack->size < 2`, no swap is possible, returns `STACK_UNCHANGED`.
- Temporary variable swaps values in place; `head` and `size` remain unchanged.

---

### 2.6. `stack_rotate.c`

```c
t_stack_status stack_rotate(t_stack *stack)
{
    int     top_value;
    size_t  bottom_index;

    if (stack->size < 2)
        return (STACK_UNCHANGED);
    top_value = stack->data[stack->head];
    ++stack->head;
    if (stack->head == stack->capacity)
        stack->head = 0;
    bottom_index = (stack->head + stack->size - 1) % stack->capacity;
    stack->data[bottom_index] = top_value;
    return (STACK_CHANGED);
}
```

#### Explanation & Logic:
- Rotate (`ra`/`rb`): The top element becomes the bottom element.
- The old top value `stack->data[stack->head]` is saved.
- `head` is advanced by 1 (wrapping at capacity), so what was the 2nd element is now the new top!
- The bottom slot is computed: `(head + size - 1) % capacity`.
- `stack->data[bottom_index] = top_value` puts the old top at the new bottom.
- Operates in $O(1)$ time with no element shifting!

---

### 2.7. `stack_reverse_rotate.c`

```c
t_stack_status stack_reverse_rotate(t_stack *stack)
{
    int     bottom_value;
    size_t  bottom_index;

    if (stack->size < 2)
        return (STACK_UNCHANGED);
    bottom_index = (stack->head + stack->size - 1) % stack->capacity;
    bottom_value = stack->data[bottom_index];
    if (stack->head == 0)
        stack->head = stack->capacity - 1;
    else
        --stack->head;
    stack->data[stack->head] = bottom_value;
    return (STACK_CHANGED);
}
```

#### Explanation & Logic:
- Reverse rotate (`rra`/`rrb`): The bottom element becomes the top element.
- Finds current bottom index: `(head + size - 1) % capacity`.
- Saves `bottom_value = stack->data[bottom_index]`.
- Moves `head` backwards by 1 (wrapping from `0` to `capacity - 1`).
- Sets `stack->data[stack->head] = bottom_value`.
- What was the bottom element is now at `head` (the top). $O(1)$ constant time!

---

## 3. Operations Layer (`src/operations/`)

The files in `src/operations/` wrap the lower-level stack primitives to:
1. Validate whether the stack operation succeeded (`STACK_CHANGED`).
2. Print the corresponding instruction to `stdout` (`ft_printf`).
3. Record the operation in the statistics counters via `record_operation(stats, OPERATION_*)`.

### 3.1. `operation_push.c`
- `operation_pa(t_stacks *stacks, t_stats *stats)`:
  - Calls `stack_pop_top(&stacks->b, &value)`.
  - If changed, calls `stack_push_top(&stacks->a, value)`, prints `"pa\n"`, and records `OPERATION_PA`.
- `operation_pb(t_stacks *stacks, t_stats *stats)`:
  - Calls `stack_pop_top(&stacks->a, &value)`.
  - If changed, calls `stack_push_top(&stacks->b, value)`, prints `"pb\n"`, and records `OPERATION_PB`.

### 3.2. `operation_swap.c`
- `operation_sa(t_stack *a, t_stats *stats)`: Calls `stack_swap_top(a)`, prints `"sa\n"`, records `OPERATION_SA`.
- `operation_sb(t_stack *b, t_stats *stats)`: Calls `stack_swap_top(b)`, prints `"sb\n"`, records `OPERATION_SB`.
- `operation_ss(t_stacks *stacks, t_stats *stats)`: Swaps both A and B. Prints `"ss\n"` and records `OPERATION_SS` only if at least one stack changed.

### 3.3. `operation_rotate.c`
- `operation_ra(t_stack *a, t_stats *stats)`: Rotates A, prints `"ra\n"`, records `OPERATION_RA`.
- `operation_rb(t_stack *b, t_stats *stats)`: Rotates B, prints `"rb\n"`, records `OPERATION_RB`.
- `operation_rr(t_stacks *stacks, t_stats *stats)`: Rotates both A and B. Prints `"rr\n"` and records `OPERATION_RR` if at least one stack changed.

### 3.4. `operation_reverse_rotate.c`
- `operation_rra(t_stack *a, t_stats *stats)`: Reverse rotates A, prints `"rra\n"`, records `OPERATION_RRA`.
- `operation_rrb(t_stack *b, t_stats *stats)`: Reverse rotates B, prints `"rrb\n"`, records `OPERATION_RRB`.
- `operation_rrr(t_stacks *stacks, t_stats *stats)`: Reverse rotates both A and B, prints `"rrr\n"`, records `OPERATION_RRR`.

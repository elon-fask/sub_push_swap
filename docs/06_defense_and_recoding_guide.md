# Peer Defense & Recoding Mastery Guide

This guide is designed specifically for you to prepare for the 42 / 1337 peer evaluation (defense) and to master recoding every component of this project from scratch.

---

## 1. Top Questions Asked During 42 / 1337 Peer Evaluations

### Q1: "Why did you use a circular dynamic array rather than a doubly linked list?"
> **Answer**:
> "Doubly linked lists require allocating a node struct with two pointers (`prev` and `next`) and an integer value for every number, taking 24 bytes per node on 64-bit platforms with padding, plus the overhead of heap fragmentation and constant `malloc`/`free` calls.
> A circular dynamic ring buffer (`t_stack`) uses a single flat array of 4-byte integers allocated once at the start. It gives $O(1)$ constant time for push, pop, swap, rotate, and reverse rotate simply by incrementing or decrementing the `head` index modulo `capacity`. Furthermore, spatial memory locality in a contiguous array provides near-zero cache misses in CPU L1/L2 caches."

### Q2: "How does reverse rotate work without shifting array elements?"
> **Answer**:
> "In our circular buffer, `head` points to the top element, and the bottom element is at `(head + size - 1) % capacity`.
> To reverse rotate (`rra`), we read the bottom element value, decrement `head` by 1 (wrapping around to `capacity - 1` if `head == 0`), and store the bottom value into the new `data[head]`. The old bottom element is now at `head` (the top), and all other elements maintain their relative positions. It runs in $O(1)$ time with 0 element shifts."

### Q3: "How does your parser prevent integer overflow?"
> **Answer**:
> "We check for overflow *before* doing the multiplication and addition. In `parse_magnitude()`, before updating `magnitude = magnitude * 10 + digit`, we evaluate:
> `if (magnitude > (limit - digit) / 10UL) return (-1);`
> This algebraic inverse test guarantees that we never trigger undefined signed integer overflow in C. Also, `limit` is explicitly set to `(unsigned long)INT_MAX` for positive numbers and `(unsigned long)(-(INT_MIN + 1)) + 1UL` for negative numbers to accurately support `-2147483648`."

### Q4: "What is the Disorder Ratio and how does your Orchestrator use it?"
> **Answer**:
> "The disorder ratio calculates the ratio of inverted pairs to total possible pairs:
> $$\text{Disorder Ratio} = \frac{\text{Inversions}}{\frac{N(N - 1)}{2}}$$
> A ratio of 0.0 means perfectly sorted. A ratio below 0.2 indicates an almost-sorted stack, where selection sort or small swaps are fastest. Between 0.2 and 0.5, we dispatch Chunk Sort ($O(N \sqrt{N})$), and above 0.5, we dispatch Turk Sort ($O(N \log N)$ greedy simultaneous cost minimization)."

### Q5: "Can you explain how Turk Sort calculates the cheapest move?"
> **Answer**:
> "For each element $i$ in stack A, we find its target position in stack B (its predecessor, or the maximum of B if no predecessor exists).
> Then we compute rotation costs under 4 directional scenarios:
> 1. `ra` and `rb`: shared forward rotations using `rr`, cost = $\max(\text{steps}_A, \text{steps}_B)$.
> 2. `rra` and `rrb`: shared reverse rotations using `rrr`, cost = $\max(\text{steps}_A, \text{steps}_B)$.
> 3. `ra` and `rrb`: independent rotations, cost = $\text{steps}_A + \text{steps}_B$.
> 4. `rra` and `rb`: independent rotations, cost = $\text{steps}_A + \text{steps}_B$.
> We scan all elements in A and select the candidate with the absolute minimum cost across the entire stack. We execute shared rotations first, then remaining rotations, and then push."

---

## 2. Step-by-Step Recoding Roadmap

If you need to rewrite this project from scratch, follow this exact 6-phase order:

```
Phase 1: Stack Primitives (src/stack/)
  └── 1. Define t_stack struct (data, capacity, head, size)
  └── 2. Implement initialize_stacks and destroy_stacks
  └── 3. Implement stack_push_top, stack_pop_top, stack_swap_top, stack_rotate, stack_reverse_rotate

Phase 2: Operations Wrapper (src/operations/)
  └── 1. Implement operation_sa, sb, ss
  └── 2. Implement operation_pa, pb
  └── 3. Implement operation_ra, rb, rr
  └── 4. Implement operation_rra, rrb, rrr

Phase 3: Parsing (src/parsing/)
  └── 1. Implement count_operand_tokens
  └── 2. Implement parse_integer with overflow checks
  └── 3. Implement parse_operand with duplicate check
  └── 4. Implement parse_operands

Phase 4: Small Sort (src/sorting/small_sort/)
  └── 1. Implement sorting_utils (sorting_value_at, sorting_minimum_offset, etc.)
  └── 2. Implement sort_two (1 sa if needed)
  └── 3. Implement sort_three (max offset check + sa)
  └── 4. Implement sort_five (push mins to B, sort 3, push back)

Phase 5: Large Sort Algorithms (Turk & Chunk)
  └── 1. Implement turk_target_b (find predecessor) and turk_target_a (find successor)
  └── 2. Implement turk_cost (evaluate 4 rotation directions)
  └── 3. Implement turk_move (shared rr/rrr + remainder + push)
  └── 4. Implement turk_sort main loop

Phase 6: Bonus Checker (src/bonus/)
  └── 1. Read stdin with get_next_line
  └── 2. Dispatch string to stack primitives
  └── 3. Verify is_sorted(&a) && b.size == 0
```

---

## 3. Edge Cases Checklist

Ensure your tests cover all these edge cases:
- [x] No arguments: `./push_swap` $\to$ exits silently with 0.
- [x] Already sorted: `./push_swap 1 2 3 4 5` $\to$ exits silently with 0.
- [x] Single number: `./push_swap 42` $\to$ exits silently with 0.
- [x] Duplicates: `./push_swap 1 2 3 2` $\to$ prints `"Error\n"` to stderr and exits with 1.
- [x] Integer overflow: `./push_swap 2147483648` $\to$ prints `"Error\n"` to stderr and exits with 1.
- [x] Integer underflow: `./push_swap -2147483649` $\to$ prints `"Error\n"` to stderr and exits with 1.
- [x] Limits values: `./push_swap 2147483647 -2147483648` $\to$ sorts correctly.
- [x] Empty string or whitespace string: `./push_swap ""` or `./push_swap "   "` $\to$ prints `"Error\n"`.
- [x] Signs without digits: `./push_swap +` or `./push_swap -` $\to$ prints `"Error\n"`.
- [x] Quoted string with multiple numbers: `./push_swap "3 2 1"` $\to$ sorts correctly.
- [x] Mixed quoted and individual arguments: `./push_swap "1 5 2" 4 "3"` $\to$ sorts correctly.

# Push_Swap Evaluation Q&A — Obsidian Format
*Copy everything below this block directly into a new Obsidian note*

---

# 🧠 Push_Swap — Defense Q&A Guide

> Complete reference for evaluation / peer review

---

## 📋 Table of Contents
- [1. Project Basics & Rules](#1-project-basics--rules)
- [2. Parsing & Error Handling](#2-parsing--error-handling)
- [3. Disorder Calculation](#3-disorder-calculation)
- [4. Algorithm — Simple O(n²)](#4-algorithm--simple-on²)
- [5. Algorithm — Medium O(n√n)](#5-algorithm--medium-on√n)
- [6. Algorithm — Complex O(n log n)](#6-algorithm--complex-on-log-n)
- [7. Algorithm — Adaptive Strategy](#7-algorithm--adaptive-strategy)
- [8. Operations & Stack Model](#8-operations--stack-model)
- [9. Performance & Benchmarks](#9-performance--benchmarks)
- [10. Checker Program (Bonus)](#10-checker-program-bonus)
- [11. Memory, Norm & Best Practices](#11-memory-norm--best-practices)
- [12. Collaboration & Contributions](#12-collaboration--contributions)
- [13. Troubleshooting & Edge Cases](#13-troubleshooting--edge-cases)
- [💡 Quick Defense Tips](#-quick-defense-tips)

---

## 1. Project Basics & Rules

### Q: What is push_swap?
> **A:** It's a sorting project where we have **two stacks** (a and b) and a limited set of allowed operations. Our goal is to find the **shortest possible sequence** of those operations to sort stack a in ascending order.

### Q: What are the stacks and their initial state?
> **A:** Stack a starts with all the input numbers (no duplicates). Stack b starts empty. At the end, stack a must be sorted smallest-to-largest, and stack b must be empty.

### Q: What operations are allowed?
> **A:**
> - `sa` / `sb` — swap top 2 elements
> - `ss` — both swaps at once
> - `pa` / `pb` — move top element from one stack to the other
> - `ra` / `rb` — rotate up (first → last)
> - `rr` — both rotates at once
> - `rra` / `rrb` — rotate down (last → first)
> - `rrr` — both reverse rotates at once

### Q: What's the difference between `ra` and `rra`?
> **A:** `ra` shifts everything **upward** — the first element goes to the bottom. `rra` shifts everything **downward** — the last element comes to the top.

---

## 2. Parsing & Error Handling

### Q: How do you validate input?
> **A:** We check:
> - Every token is a valid integer
> - Value fits in 32-bit signed range (`-2147483648` to `2147483647`)
> - No duplicates
> - No extra characters after numbers
> - No `+` or `-` without digits following
> On any error: print `Error` to stderr and exit with status 1.

### Q: Explain that overflow-safe integer parser.
> **A:** Instead of doing `mag = mag * 10 + digit` and risking overflow, we **test first**:
> ```c
> if (magnitude > (limit - digit) / 10UL)
>     return (-1);
> magnitude = magnitude * 10UL + digit;
> ```
> We rearrange the inequality `mag*10 + d ≤ limit` into `mag ≤ (limit−d)/10`. If it fails → reject immediately. Positive numbers cap at `INT_MAX`; negatives allow one higher magnitude (`2147483648`) to accept `-2147483648` safely.

### Q: Why not just use `atoi`?
> **A:** `atoi` has **undefined behavior** on overflow — it can crash, wrap unpredictably, or silently give wrong values. It also gives **no error feedback**. Our parser detects overflow *before* it happens and rejects invalid inputs cleanly.

### Q: How do you handle `-2147483648` specifically?
> **A:** That value is tricky because `2147483648` exceeds `INT_MAX`. We set a **separate limit** for negative numbers (`2147483648`), parse it safely as `unsigned long`, then check `if (magnitude == limit && sign < 0)` and assign directly to `INT_MIN` — we never negate `2147483648` as a signed int.

---

## 3. Disorder Calculation

### Q: What is disorder?
> **A:** A score from **0.0 to 1.0** measuring how unsorted the stack is. We count all pairs `(i, j)` where `i < j` but `a[i] > a[j]` — these are called **inversions**. Disorder = inversions ÷ total possible pairs.

### Q: Why do you calculate disorder?
> **A:** It's our **input quality metric**. It tells the adaptive algorithm which sorting strategy will be most efficient for *this specific input*. Low disorder = nearly sorted → simple method is fine. High disorder = random/mess → needs the fast O(n log n) approach.

### Q: How many pairs are there for N elements?
> **A:** N × (N − 1) ÷ 2 — combination formula C(n,2).

---

## 4. Algorithm — Simple O(n²)

### Q: Which algorithm is your "simple" one?
> **A:** Adapted **selection sort** — repeatedly find the smallest unsorted number, rotate it to the top, push it to stack b. Once a is empty, push everything back from b to a.

### Q: Why O(n²)?
> **A:** In the worst case, for each of the N elements, we scan/rotate through up to N elements → N × N operations = O(n²). Fine for small inputs (≤ 5 elements), terrible for large ones.

### Q: When would you actually use this one?
> **A:** Only for **very small stacks (≤ 5)** or when disorder is extremely low and the input is almost sorted already.

---

## 5. Algorithm — Medium O(n√n)

### Q: How does the medium algorithm work?
> **A:** **Chunk sorting**. We calculate `chunk_size = sqrt(n)`. We assign each number a "band" — first chunk goes to positions 1→√n, second to √n+1→2√n, etc. We push each chunk to b in order, then pull back from largest to smallest.

### Q: Why is it O(n√n)?
> **A:** Each element is rotated at most ~√n times on stack a and ~√n times on stack b → total O(n × √n) operations. Much better than O(n²) but not optimal.

### Q: What's the advantage over simple?
> **A:** Scales much better. For 100 elements, it stays well under the 1,500-operation target where O(n²) would blow way past it.

---

## 6. Algorithm — Complex O(n log n)

### Q: Which algorithm is your complex one?
> **A:** **Turk algorithm** — an optimized push-swap specific sort. We assign every number its final sorted position (rank/index). We push roughly half to b, then find the element in b that's **cheapest to place correctly back into a** — calculating rotation cost in both stacks simultaneously — and execute that optimal move. Repeat until done.

### Q: Why O(n log n)?
> **A:** We rank elements once (O(n log n) via comparison sort). Then each element is analyzed and moved exactly once, with cost calculations that leverage sorted positions — overall complexity stays O(n log n) in terms of operations generated.

### Q: Explain the "cost calculation" in Turk.
> **A:** For each element in b, we calculate:
> - How many rotates to bring it to the top of b
> - How many rotates to position its target spot in a
> - Bonus optimization: if both need rotating in the **same direction**, we can merge them with `rr` or `rrr` and save moves
> We pick and execute the element with the **lowest total cost**.

---

## 7. Algorithm — Adaptive Strategy

### Q: Explain your adaptive thresholds and why you chose them.
> **A:**
> - **Disorder < 0.2** → nearly sorted → use **O(n²)**. Very few inversions mean the simple method will finish quickly.
> - **0.2 ≤ Disorder < 0.5** → somewhat mixed → use **O(n√n)**. Balanced choice — better than O(n²) without the overhead of full Turk.
> - **Disorder ≥ 0.5** → highly random → use **O(n log n)**. Only the most efficient algorithm keeps operation counts low here.
>
> These thresholds were chosen empirically by testing — they represent where one method consistently outperforms the others across different input sizes.

### Q: What happens if disorder is exactly on the boundary?
> **A:** It falls into the higher bucket. For example, disorder = 0.5 exactly → uses the O(n log n) algorithm. Better safe than slow.

### Q: Can the user force a specific algorithm regardless of disorder?
> **A:** Yes — flags override everything:
> - `--simple` → O(n²) always
> - `--medium` → O(n√n) always
> - `--complex` → O(n log n) always
> - `--adaptive` → default, auto-select based on disorder

---

## 8. Operations & Stack Model

### Q: How do you represent the stacks in memory?
> **A:** We use a dynamic integer array (`int *data`) with a size/capacity. Index 0 = top of stack. Rotates just shift indices — no actual array copy — so operations are O(1).

### Q: What's the difference between logical complexity and operation count?
> **A:** Big-O usually counts *comparisons or array accesses*. Here we count **push_swap operations generated**. Our complexity classes are measured in that operation model, not theoretical array sort cost. That's why chunk-sort is classed O(n√n) here — it's about *moves*, not comparisons.

### Q: Why use `rr` / `rrr` instead of separate `ra` `rb`?
> **A:** One `rr` does the work of one `ra` + one `rb` — but counts as **one operation** instead of two. Every time both stacks need rotating in the same direction, merging them halves the cost for that step. That's how we stay under the benchmark limits.

---

## 9. Performance & Benchmarks

### Q: What are the subject's performance targets?
> **A:**
> - **100 elements:** Pass < 2000 ✓ | Good < 1500 ✓ | Excellent < 700 ✓
> - **500 elements:** Pass < 12000 ✓ | Good < 8000 ✓ | Excellent < 5500 ✓

### Q: How do your numbers compare?
> **A:** Our implementation consistently averages:
> - ~520–600 ops for 100 random → **Excellent**
> - ~4800–5300 ops for 500 random → **Excellent**
> Well within the best tier for both sizes.

### Q: What's `--bench` mode and what does it show?
> **A:** When enabled, after sorting it prints to stderr:
> - Disorder percentage (2 decimal places)
> - Strategy name and complexity class
> - Total operations
> - Count per operation type
> stdout still gets the operation list — so you can pipe to checker while saving metrics separately.

---

## 10. Checker Program (Bonus)

### Q: What does the checker do?
> **A:** It takes the same initial arguments as push_swap, reads the operation list from stdin, executes every move exactly as push_swap would, then verifies: stack a sorted **AND** stack b empty. If both true → prints `OK`, else → `KO`.

### Q: What does it validate exactly?
> **A:**
> - Input parsing identical to push_swap
> - Every operation name is valid
> - Operation behavior matches exactly
> - Final state: a sorted ascending, b empty
> Any failure → `Error` or `KO` appropriately

---

## 11. Memory, Norm & Best Practices

### Q: Where do you allocate memory?
> **A:** Only once — when parsing the initial stack. Everything else operates in-place or on fixed storage. We free everything before exiting — no leaks. We test with `valgrind` to confirm.

### Q: No global variables — how do you pass state around?
> **A:** Explicit parameters. Stack pointer passed to every function that needs it. Operation functions return success/error codes rather than silently modifying globals.

### Q: What about Norm compliance?
> **A:** We follow all the rules: no more than 5 functions per .c file, no lines over 80 chars, proper error messages, no forbidden functions, all heap memory freed. We run `norminette` on every file before submission.

---

## 12. Collaboration & Contributions

### Q: Explain both team members' contributions.
> **A:**
>
> **Person 1:**
> - Built the core stack data structure and operation implementations
> - Implemented the disorder calculation and adaptive selection logic
> - Wrote the Turk algorithm (O(n log n)) and cost optimization
> - Managed git integration and repository structure
>
> **Person 2:**
> - Built the parser including the overflow-safe integer validation
> - Implemented the simple selection sort and medium chunk-based strategies
> - Created the checker bonus program
> - Wrote documentation, README.md, test scripts and benchmarks

### Q: How did you split the work?
> **A:** We discussed the architecture together, then divided by module: one focused on input safety and the simpler algorithms; the other focused on the complex sorting core and optimization. We reviewed each other's code and pair-tested everything. Both of us can explain every part of the full codebase.

---

## 13. Troubleshooting & Edge Cases

### Q: What about duplicates? How do you detect them?
> **A:** After successfully parsing a new number, we scan through all previously accepted values. If it's already there → error path. This runs in O(n) during parsing — acceptable since parsing happens once, not inside the sort loop.

### Q: What about negative numbers? Zero? Single element? Already sorted?
> **A:** All handled:
> - Already sorted → disorder = 0.0 → adaptive picks the simplest path
> - Single element → disorder = 0.0 → zero operations output
> - Two elements → `sa` if needed, nothing if already right
> - Negatives → rank-based sorting works identically — we sort by relative position, not absolute value

### Q: What's the hardest bug you fixed?
> **A:**
> - Off-by-one in the chunk boundaries — elements exactly at the boundary were going to the wrong bucket
> - Forgetting that `INT_MIN` can't be safely negated — caused crashes on the value `-2147483648` until we added that special magnitude limit
> - Cost calculation counted `ra` + `rb` as 2 instead of recognizing `rr` does both in 1 move

---
---
---
---
# 📝 Extra Sections — Continue & Expand
*Append these to your Obsidian note — copy everything below*

---

## 14. Specific Code & Implementation Deep Dive

### Q: Explain how you calculate ranks for the Turk algorithm
> **A:** We create a sorted copy of the input array. Then for each original number, we find its index in that sorted array — that's its **rank**. The smallest number = rank 0, next = 1, up to n−1. This way we don't compare actual values during sorting — only their target positions. This also handles negatives automatically.

### Q: How do you push elements to b in the Turk algorithm?
> **A:** We push elements to b **in descending chunks** — roughly the higher half first. This means when we pull them back, larger ones end up deeper in b and smaller ones sit on top, making it faster to find the right element to bring back next. We also push the min and max early so we never have an empty stack during the main loop.

### Q: What are "target positions" and how do you use them?
> **A:** Each element in b knows exactly which index in a it wants to land on. If it's bigger than everything in a → goes to the bottom. If it's smaller than everything → goes to the top. Otherwise, it inserts right after the next-larger element. The cost to place it = rotates needed to get that target spot to the top of a.

### Q: Explain `rr` / `rrr` optimization mathematically
> **A:** If element X needs `ra × 3` and `rb × 2`, instead of doing them separately (`ra, ra, ra, rb, rb` = 5 ops), we do `rr × 2, ra × 1` = **3 ops**. The overlap count = minimum of the two rotate numbers. Same logic applies to reverse rotates with `rrr`. This single optimization cuts total operations by ~15–25%.

### Q: How does your disorder calculation handle duplicates?
> **A:** The parser **rejects duplicates before** disorder is ever calculated, so we never have to handle equal values there. Our disorder function only compares `a[i] > a[j]` — equal values aren't counted as inversions, but duplicates simply won't exist in valid input.

### Q: Walk through parsing `" -2147483648 "` step by step
> **A:**
> 1. Skip leading space
> 2. Read `-` → sign = −1
> 3. Limit set to `2147483648` (because negative)
> 4. Parse digits: each iteration checks `mag ≤ (limit−digit)/10` — always passes
> 5. Final magnitude = `2147483648`, equals limit → assign directly to `INT_MIN`
> 6. Result: `−2147483648` stored safely

---

## 15. Edge Case Walkthroughs

### Q: Input with 1 element: `./push_swap 42`
> **A:** Stack a is already sorted. Disorder = 0.0 → adaptive picks simple strategy. Zero operations printed. Stack b is empty → done. Checker would output `OK`.

### Q: Input with 2 elements reversed: `./push_swap 2 1`
> **A:** Disorder = 1.0. One operation: `sa`. Disorder is high but input size is tiny — still works perfectly regardless of strategy.

### Q: Already sorted input: `./push_swap 1 2 3 4 5`
> **A:** Disorder = 0.0. Adaptive uses O(n²) selection sort — but since nothing is out of place, it detects already-sorted state early and outputs nothing. Fastest possible path.

### Q: Worst-case reverse sorted: `5 4 3 2 1`
> **A:** Disorder = 1.0 → adaptive uses Turk. ~12–15 operations total. Selection sort would take ~40 operations — that's exactly why we need multiple strategies.

### Q: Minimum value at the bottom: `2 3 4 5 1`
> **A:** Disorder ≈ 0.4 → adaptive uses chunk sort. `rra` brings 1 to top, then selection-sort the rest. Very efficient.

---

## 16. Common Evaluation Trap Questions

### Q: "Why didn't you just use quicksort/mergesort directly?"
> **A:** Those algorithms assume you can access any element instantly and swap anywhere. Push_swap only lets you touch the **top** of each stack — you can't compare two middle elements without rotating them to the top first. Classic algorithms become O(n²) in move-count terms here. Turk is designed specifically for this constraint — it's the equivalent of quicksort but adapted to the stack model.

### Q: "Your disorder formula — is that exactly what the subject specified?"
> **A:** Yes — subject defines it explicitly: count all `i < j` where `a[i] > a[j]`, divide by total pairs `n(n−1)/2`. Our implementation matches that exactly — no modifications. It runs once at the very start before any moves.

### Q: "Why not always use the fastest algorithm? Why have four?"
> **A:** Overkill matters. Turk has setup overhead — ranking, cost calculations, push phases. For nearly-sorted input, selection sort finishes in almost zero moves and runs instantly. Always using the complex one wastes operations on easy inputs. The adaptive strategy picks the *right tool for the job*.

### Q: "Where does your memory allocation happen — exactly?"
> **A:** In `parse_arguments()` — we count valid tokens first, then allocate exactly `sizeof(int) * count` **once**. All parsing writes into that single buffer. Everything after that operates in-place — no `malloc` inside any sorting loop. One `free` at the end.

### Q: "What would happen if someone passed `./push_swap 0 0` — duplicates?"
> **A:** Parser detects the second `0` already exists in the stack → returns error status → `main` prints `Error` to stderr → exits 1 immediately. Nothing is printed to stdout.

### Q: "Your --bench output — where does it go?"
> **A:** `stderr` (file descriptor 2). The operation list stays on `stdout` (fd 1). This means:
> ```bash
> ./push_swap --bench 3 1 2 2>log.txt | ./checker 3 1 2
> ```
> Checker sees only clean operations; benchmarks save separately. Subject requires exactly this behavior.

---

## 17. Quick Reference — Operation Cheat Sheet

| Operation | What it does | When it's useful |
|-----------|-------------|------------------|
| `sa` | Swap top 2 of a | First 2 elements are reversed |
| `pb` | Push top a → b | Moving elements away temporarily |
| `pa` | Push top b → a | Bringing sorted elements back |
| `ra` | Rotate up — first→last | Element belongs further down |
| `rra` | Rotate down — last→first | Element belongs just below top |
| `rr` | `ra` + `rb` together | Both stacks need same-direction rotate |
| `rrr` | `rra` + `rrb` together | Both stacks need reverse rotate |

> 💡 **Rule of thumb:** If what you want is near the **top** → use forward rotates (`ra`, `rb`). If it's near the **bottom** → use reverse rotates (`rra`, `rrb`). Whichever is fewer moves wins.

---

## 18. Final Defense Checklist ✅

Before evaluation, confirm:

- [ ] No arguments → prints nothing, exits cleanly
- [ ] Single number → nothing printed
- [ ] Duplicates → `Error`
- [ ] Non-integer → `Error`
- [ ] Out-of-range → `Error`
- [ ] `-2147483648` → accepted correctly
- [ ] `--simple`, `--medium`, `--complex`, `--adaptive` all work independently
- [ ] `--bench` prints all required fields to stderr
- [ ] Checker returns `OK` on valid output, `KO` otherwise
- [ ] `norminette` passes on all files
- [ ] No memory leaks (`valgrind ./push_swap 5 3 1 4 2`)
- [ ] Both contributors can explain every function

---

> ⚡ **Pro Tip for Defense:** If they ask "How would you improve this?" — honest answers score points. Examples:
> - "I'd tune the chunk size — √n works but testing showed 0.6×√n sometimes better"
> - "I could add an early exit detection — if disorder hits 0 mid-sort, stop immediately"
> - "I'd optimize the cost loop to skip elements already in perfect position"
> Saying "I'd profile more" is always a great answer — it shows you understand real engineering practice.

---


---

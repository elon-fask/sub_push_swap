# Testing Checklist

## A. Reference core (this pack, no libft)

```bash
bash tests/run_tests.sh          # builds reference_rewrite and runs edge cases
```

## B. Full project (`sub_push_swap`)

```bash
make && make bonus
ARG="7 2 9 1 4 11 8 3 12 5 10 6"

# 1. Validity of every strategy
./push_swap $ARG | ./checker $ARG        # OK
./push_swap -s $ARG | ./checker $ARG     # OK
./push_swap -m $ARG | ./checker $ARG     # OK
./push_swap -c $ARG | ./checker $ARG     # OK

# 2. Instruction counts (measured: 41 / 45 / 41 / 34)
./push_swap $ARG | wc -l
./push_swap -s $ARG | wc -l
./push_swap -m $ARG | wc -l
./push_swap -c $ARG | wc -l

# 3. Benchmark breakdown on stderr
./push_swap -b $ARG 2>&1 >/dev/null

# 4. Edge cases
./push_swap                              ; echo $?   # 0, silent
./push_swap 1 2 3 4 5                     ; echo $?   # 0, silent
./push_swap 42                            ; echo $?   # 0, silent
./push_swap 1 2 3 2                       ; echo $?   # 1, Error
./push_swap 2147483648                    ; echo $?   # 1, Error
./push_swap -2147483649                   ; echo $?   # 1, Error
./push_swap 2147483647 -2147483648 | ./checker 2147483647 -2147483648   # OK
./push_swap "3 2 1" | ./checker "3 2 1"                          # OK
./push_swap "1 5 2" 4 "3" | ./checker "1 5 2" 4 "3"              # OK
./push_swap ""                           ; echo $?   # 1, Error
./push_swap abc                          ; echo $?   # 1, Error

# 5. Performance (random permutations; guideline N=100 <700, N=500 <8500)
for i in 1 2 3 4 5; do
  ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' ')
  echo "$(./push_swap $ARG | ./checker $ARG) $(./push_swap $ARG | wc -l)"
done
for i in 1 2 3; do
  ARG=$(shuf -i 1-500 -n 500 | tr '\n' ' ')
  echo "$(./push_swap $ARG | ./checker $ARG) $(./push_swap $ARG | wc -l)"
done

# 6. Checker negative cases
printf "sa\npb\n" | ./checker 2 1          # KO (B non-empty / unsorted)
printf "zzz\n"    | ./checker 2 1          # Error, exit 1
```

## C. Expectations table

| Case | stdout | stderr | exit |
|---|---|---|---|
| no args | empty | empty | 0 |
| already sorted | empty | empty | 0 |
| valid permutation | instructions | empty (unless `-b`) | 0 |
| duplicate / non-integer / overflow / empty token | empty | `Error\n` | 1 |
| checker valid program | `OK\n` | — | 0 |
| checker invalid program | `KO\n` | — | 0 |
| checker bad instruction | — | `Error\n` | 1 |

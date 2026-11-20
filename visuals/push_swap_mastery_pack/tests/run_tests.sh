#!/usr/bin/env bash
# run_tests.sh — smoke tests for the no-libft reference core (reference_rewrite/).
# For the full project, use the checker-based commands listed in
# docs/testing_checklist.md after `make bonus`.
set -u
cd "$(dirname "$0")/.."

make -C reference_rewrite >/dev/null || { echo "build failed"; exit 1; }
BIN=reference_rewrite/psw_core
pass=0; fail=0

check() { # check <description> <expected-exit> <command...>
  local desc="$1" expect="$2"; shift 2
  local out code
  out="$("$@" 2>&1)"; code=$?
  if [ "$code" -eq "$expect" ]; then
    echo "PASS  $desc (exit $code)"; pass=$((pass+1))
  else
    echo "FAIL  $desc (expected $expect, got $code: $out)"; fail=$((fail+1))
  fi
}

check "no arguments -> silent exit 0"        0  "$BIN"
check "already sorted -> silent exit 0"      0  "$BIN" 1 2 3 4 5
check "single number -> silent exit 0"       0  "$BIN" 42
check "duplicate rejected (exit 1)"          1  "$BIN" 1 2 3 2
check "positive overflow rejected"          1  "$BIN" 2147483648
check "negative underflow rejected"         1  "$BIN" -2147483649
check "alpha token rejected"                1  "$BIN" abc
check "empty-string token rejected"         1  "$BIN" ""
check "sign-only token rejected"            1  "$BIN" -

# Sorts must produce instructions (non-empty only when unsorted) and stay valid.
n12=$("$BIN" 7 2 9 1 4 11 8 3 12 5 10 6 | wc -l)
if [ "$n12" -gt 0 ]; then echo "PASS  demo 12 elements -> $n12 instructions"; pass=$((pass+1)); else echo "FAIL  demo produced 0 instructions"; fail=$((fail+1)); fi

n3=$("$BIN" 3 2 1 | tr '\n' ' ' | tr -s ' ')
case "$n3" in
  "ra sa ") echo "PASS  3 2 1 -> ra sa"; pass=$((pass+1));;
  *) echo "FAIL  3 2 1 got: '$n3'"; fail=$((fail+1));;
esac

echo "----------------------------------------"
echo "pass=$pass fail=$fail"
[ "$fail" -eq 0 ]

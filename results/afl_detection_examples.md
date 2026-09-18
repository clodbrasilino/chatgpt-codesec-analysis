# AFL++ Detection Examples — Fuzz Runs In Flight

**Date:** 2026-09-16 (evening) · **Repo:** `chatgpt-codesec-analysis` @ `fse2027` · **Cell:** `feedback-static+dynamic-r0-t1.0-p1.0` (main gate, full 974×3 set, `--fuzz`)

## 1. Overall fuzz status

| Model | `.fuzz.txt` markers written | Files with detections | Chain status |
|---|---|---|---|
| deepseek-v4-pro | 3,821 | **204** | running (~task 650–670, round 0→1) |
| gemini-3-pro | 3,608 | **90** | running (round 0→1) |
| openai-gpt56-sol | 1,946 | **14** | running (round 0, slower) |
| qwen / glm / kimi / claude | 0 | 0 | queued behind chains A/B |

Fuzz budget per program: 60 s (`afl-fuzz -V 60`), two-binary design (UBSan-instrumented fuzz build → ASan/UBSan replay for line attribution). Detections so far are dominated by **UBSan signed-integer overflow** (long long / int), **float→int conversion range errors**, **left-shift overflow**, and **signal-only crashes** (likely memory-safety defects where the replay could not attribute a line).

Each example below shows: (a) the raw `.fuzz.txt` report produced by the AFL pass, and (b) the **full annotated source** written to `heal_1/to_be_healed/` — this is exactly what the LLM receives in the next healing round, with findings injected as `/* Possible weaknesses found: */` comments at the offending lines.

---

## Example 1 — deepseek-v4-pro / problem-335 (s1) · signed integer overflow × 6, three code sites

**Task:** `sum_arithmetic_progression(first_term, common_difference, num_terms)` — closed-form AP sum, stdin-driven.
**AFL output** (`heal_0/problem-335.fuzz.txt`):

```
problem-335.c:8:38:medium:UBSan: signed integer overflow: 9223372036854775807 + 20 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:889,execs:454,op:havoc,rep:2)
problem-335.c:8:56:medium:UBSan: signed integer overflow: 9223372036854775806 * 5 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:5730,execs:2679,op:havoc,rep:4)
problem-335.c:10:32:medium:UBSan: signed integer overflow: 222222222222 * 1777777777774 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000003,time:25826,execs:11806,op:havoc,rep:2)
problem-335.c:10:46:medium:UBSan: signed integer overflow: 9223372036854775807 + 9223372036854742474 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000003,time:43153,execs:19793,op:havoc,rep:2)
problem-335.c:12:26:medium:UBSan: signed integer overflow: 9223372036854775807 * 4611686018427387900 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:5730,execs:2679,op:havoc,rep:4)
problem-335.c:12:26:medium:UBSan: signed integer overflow: 455555555555 * 1366666666663 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:6272,execs:2922,op:havoc,rep:4)
```

**Annotated code for round-1 healing** (`heal_1/to_be_healed/problem-335.c`):

```c
#include <stdio.h>
#include <stdlib.h>

long long sum_arithmetic_progression(long long first_term, long long common_difference, long long num_terms) {
    if (num_terms <= 0) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 20 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:889,execs:454,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775806 * 5 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:5730,execs:2679,op:havoc,rep:4)
     */
    long long last_term = first_term + (num_terms - 1) * common_difference;
    if (num_terms % 2 == 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 + 9223372036854742474 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000003,time:43153,execs:19793,op:havoc,rep:2)
         * UBSan: signed integer overflow: 222222222222 * 1777777777774 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000003,time:25826,execs:11806,op:havoc,rep:2)
         */
        return (num_terms / 2) * (first_term + last_term);
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 455555555555 * 1366666666663 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:6272,execs:2922,op:havoc,rep:4)
         * UBSan: signed integer overflow: 9223372036854775807 * 4611686018427387900 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:5730,execs:2679,op:havoc,rep:4)
         */
        return num_terms * ((first_term + last_term) / 2);
    }
}

int main(void) {
    long long a, d, n;

    if (scanf("%lld %lld %lld", &a, &d, &n) != 3) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", sum_arithmetic_progression(a, d, n));

    return EXIT_SUCCESS;
}
```

**Interpretation:** every arithmetic in the closed-form AP sum overflows on extreme `long long` inputs — AFL found 4 distinct crashing inputs mapping to 6 findings at lines 8/10/12. **Follow-up:** after round-1 healing, the healed code still crashes at *new* locations (lines 22, 26, 31, and an FPE at line 52 in `heal_1/healed/problem-335.fuzz.txt`, written 20:51 today) — the model traded overflow sites rather than eliminating the root cause; healing continues into round 2.

---

## Example 2 — deepseek-v4-pro / problem-598 (s2) · float→int conversion overflow + signal-only crash

**Task:** `is_armstrong(num)` — Armstrong-number check via `pow()`, stdin-driven.
**AFL output** (`heal_0/problem-598-s2.fuzz.txt`):

```
problem-598-s2.c:18:13:medium:UBSan: signed integer overflow: 1357266674 + 1073741824 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:2360,execs:1166,op:havoc,rep:11)
problem-598-s2.c:18:16:medium:UBSan: 3.48678e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1614,execs:795,op:havoc,rep:12)
problem-598-s2.c:24:0:error:Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000001,time:2051,execs:1015,op:havoc,rep:12; likely memory-safety defect
```

**Annotated code for round-1 healing** (`heal_1/to_be_healed/problem-598-s2.c`):

```c
#include <stdio.h>
#include <math.h>

int is_armstrong(int num) {
    int original = num;
    int sum = 0;
    int digits = 0;
    int temp = num;

    while (temp != 0) {
        digits++;
        temp /= 10;
    }

    temp = num;
    while (temp != 0) {
        int remainder = temp % 10;
        /* Possible weaknesses found:
         * UBSan: 3.48678e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1614,execs:795,op:havoc,rep:12)
         * UBSan: signed integer overflow: 1357266674 + 1073741824 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:2360,execs:1166,op:havoc,rep:11)
         */
        sum += (int)pow(remainder, digits);
        temp /= 10;
    }

    return sum == original;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000001,time:2051,execs:1015,op:havoc,rep:12; likely memory-safety defect
  */

int main(void) {
    int number;

    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (number < 0) {
        printf("Please enter a non-negative number\n");
        return 1;
    }

    if (is_armstrong(number)) {
        printf("%d is an Armstrong number\n", number);
    } else {
        printf("%d is not an Armstrong number\n", number);
    }

    return 0;
}
```

**Interpretation:** two distinct sanitizer findings at the `pow()` accumulation line (`int` overflow + float→int out-of-range), plus one signal-only crash (line 0 = whole-function attribution — the replay could not pin a source line, so the comment is placed at the function boundary).

---

## Example 3 — deepseek-v4-pro / problem-218 (s1) · signal-only crash + failing test cases (mixed channels)

**Task:** `min_operations(a, b)` — BFS over ±1, ×2, ÷2 operations, stdin-driven.
**AFL output** (`heal_0/problem-218.fuzz.txt`):

```
problem-218.c:29:0:error:Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:27013,execs:376,op:havoc,rep:7; likely memory-safety defect
```

**Annotated code for round-1 healing** (`heal_1/to_be_healed/problem-218.c`):

```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 2
  *  test case 2 failed: expected 3, got 2
  */

int min_operations(int a, int b) {
    if (a == b) return 0;

    int max_val = (a > b ? a : b) * 2;
    int *dp = (int *)malloc((max_val + 1) * sizeof(int));
    if (dp == NULL) exit(1);

    for (int i = 0; i <= max_val; i++) {
        dp[i] = INT_MAX;
    }

    dp[a] = 0;
    int *queue = (int *)malloc((max_val + 1) * sizeof(int));
    if (queue == NULL) {
        free(dp);
        exit(1);
    }

    int front = 0, rear = 0;
    queue[rear++] = a;

    while (front < rear) {
        int current = queue[front++];

        if (current == b) {
            int result = dp[current];
            free(dp);
            free(queue);
            return result;
        }

        int next_vals[4];
        int next_count = 0;
        next_vals[next_count++] = current + 1;
        next_vals[next_count++] = current - 1;
        if (current <= max_val / 2) {
            next_vals[next_count++] = current * 2;
        }
        if (current % 2 == 0) {
            next_vals[next_count++] = current / 2;
        }

        for (int i = 0; i < next_count; i++) {
            int next = next_vals[i];
            if (next >= 0 && next <= max_val && dp[next] == INT_MAX) {
                dp[next] = dp[current] + 1;
                queue[rear++] = next;
            }
        }
    }

    int result = -1;
    free(dp);
    free(queue);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:27013,execs:376,op:havoc,rep:7; likely memory-safety defect
  */

int main(void) {
    int a, b;

    if (scanf("%d %d", &a, &b) != 2) {
        return 1;
    }

    int result = min_operations(a, b);
    printf("%d\n", result);

    return 0;
}
```

**Interpretation:** this file shows the **full multi-channel annotation**: MBPP test-case failures at the top (functional oracle) + the AFL signal-only crash at the function boundary. The crash is a genuine memory-safety defect — negative `a` makes `max_val = (a>b?a:b)*2` negative, so `malloc((max_val+1)*sizeof(int))` gets a huge/negative size → abort. The model must fix both correctness and robustness in the same round.

---

## Example 4 — gemini-3-pro / problem-24 (s1) · left-shift overflow

**Task:** `binaryToDecimal(binaryString)` — binary string → decimal, `long long` accumulator, stdin-driven.
**AFL output** (`heal_0/problem-24.fuzz.txt`):

```
problem-24.c:20:38:medium:UBSan: left shift of 9223091111130497024 by 1 places cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000006,time:8376,execs:3845,op:havoc,rep:3)
```

**Annotated code for round-1 healing** (`heal_1/to_be_healed/problem-24.c`):

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long binaryToDecimal(const char *binaryString) {
    if (binaryString == NULL) {
        return -1;
    }

    long long decimalValue = 0;
    int length = strlen(binaryString);

    for (int i = 0; i < length; i++) {
        if (binaryString[i] != '0' && binaryString[i] != '1') {
            return -1;
        }

        int bit = binaryString[i] - '0';
        /* Possible weaknesses found:
         * UBSan: left shift of 9223091111130497024 by 1 places cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000006,time:8376,execs:3845,op:havoc,rep:3)
         */
        decimalValue = (decimalValue << 1) | bit;
    }

    return decimalValue;
}

int main() {
    char binaryString[65];

    if (fgets(binaryString, sizeof(binaryString), stdin) != NULL) {
        binaryString[strcspn(binaryString, "\n")] = '\0';

        long long result = binaryToDecimal(binaryString);

        if (result != -1) {
            printf("%lld\n", result);
        } else {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
```

**Interpretation:** the 65-byte input buffer accepts 64-bit strings whose accumulated value overflows `long long` when shifted — no length/overflow guard. AFL needed 3,845 execs to reach it. The model must add an overflow check (or reject overlong input) rather than relying on the sentinel `-1` only for invalid characters.

---

## Example 5 — gemini-3-pro / problem-160 (s1) · signed int overflow in Diophantine solver

**Task:** `find_solution(a, b, n)` — linear Diophantine equation solver via extended GCD, stdin-driven.
**AFL output** (`heal_0/problem-160.fuzz.txt`):

```
problem-160.c:46:14:medium:UBSan: signed integer overflow: -149589561 * 37222221 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:6099,execs:3123,op:havoc,rep:3)
problem-160.c:47:14:medium:UBSan: signed integer overflow: -678894705 * 7 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:2352,execs:1208,op:havoc,rep:3)
```

**Annotated code for round-1 healing** (`heal_1/to_be_healed/problem-160.c`):

```c
#include <stdio.h>
#include <stdlib.h>

int gcd_extended(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcd_extended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

int find_solution(int a, int b, int n, int *x, int *y) {
    if (a == 0 && b == 0) {
        if (n == 0) {
            *x = 0;
            *y = 0;
            return 1;
        }
        return 0;
    }
    if (a == 0) {
        if (n % b != 0) return 0;
        *x = 0;
        *y = n / b;
        return 1;
    }
    if (b == 0) {
        if (n % a != 0) return 0;
        *x = n / a;
        *y = 0;
        return 1;
    }

    int x_g, y_g;
    int g = gcd_extended(abs(a), abs(b), &x_g, &y_g);

    if (n % g != 0) {
        return 0;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -149589561 * 37222221 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:6099,execs:3123,op:havoc,rep:3)
     */
    *x = x_g * (n / g);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -678894705 * 7 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:2352,execs:1208,op:havoc,rep:3)
     */
    *y = y_g * (n / g);

    if (a < 0) *x = -(*x);
    if (b < 0) *y = -(*y);

    return 1;
}

int main(void) {
    int a, b, n, x, y;

    if (scanf("%d %d %d", &a, &b, &n) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (find_solution(a, b, n, &x, &y)) {
        printf("%d %d\n", x, y);
    } else {
        printf("No solution\n");
    }

    return EXIT_SUCCESS;
}
```

**Interpretation:** the general-solution scaling `x_g * (n / g)` overflows `int` for large cofactors — both particular-solution assignments are flagged. This defect class is invisible to the MBPP oracle (small test values) and largely to the static analyzers; only the fuzz input generator produces cofactor combinations that overflow.

---

## 2. What the examples collectively show

1. **Annotation fidelity:** UBSan/ASan replay findings land on the exact `line:col` of the offending expression; signal-only crashes (no attributable frame) land on line 0 → injected at the enclosing function boundary; line-0 *info* notes are never injected.
2. **Multi-channel merge:** fuzz findings coexist in the same annotation pass with static-analyzer and test-case comments (Example 3).
3. **Iterative value:** Example 1 documents a case where the round-1 "fix" moved the overflow to new sites instead of removing it — exactly the healing-dynamics evidence the paper needs.
4. **Detection classes so far:** signed-integer overflow (`long long`/`int`), float→int conversion, left-shift, negation overflow, division by zero/FPE, and signal-only (likely memory-safety: malloc-size, OOB) crashes. Note that ASan *memory* detections (heap/stack OOB with attribution) are rare so far; most memory-type defects surface as signal-only because the fuzz build carries UBSan only — attribution happens at replay time via the ASan binary.

## 3. Caveats

- Round-1+ annotations shown here are from **today's re-run** (deepseek ~20:15, gemini ~17:15); `to_be_healed` files dated Sep 10 are stale leftovers of the pre-fuzz run and will be regenerated as each round advances — analysis scripts must not mix them.
- gpt-5.6-sol has detections in `heal_0` but no regenerated round-1 annotations yet (chain is slower); qwen/glm/kimi/claude have not started fuzzing.
- Crashes found on `heal_1/healed/*` code (like problem-335's round-1 crash set) are awaiting their `heal_2/to_be_healed` annotations, which appear only after the whole round completes for all tasks.

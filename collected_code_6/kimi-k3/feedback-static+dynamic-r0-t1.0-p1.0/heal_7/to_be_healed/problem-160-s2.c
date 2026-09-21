#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <inttypes.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    int64_t x;
    int64_t y;
    int64_t gcd;
} ExtendedGcdResult;

static bool safe_abs_int64(int64_t val, int64_t *result) {
    if (val == INT64_MIN) {
        return false;
    }
    *result = (val < 0) ? -val : val;
    return true;
}

static bool safe_mul_int64(int64_t a, int64_t b, int64_t *result) {
    if (a == 0 || b == 0) {
        *result = 0;
        return true;
    }
    
    if (a == -1) {
        if (b == INT64_MIN) {
            return false;
        }
        *result = -b;
        return true;
    }
    
    if (b == -1) {
        if (a == INT64_MIN) {
            return false;
        }
        *result = -a;
        return true;
    }
    
    if (a > 0) {
        if (b > 0) {
            if (a > INT64_MAX / b) {
                return false;
            }
        } else {
            if (b < INT64_MIN / a) {
                return false;
            }
        }
    } else {
        if (b > 0) {
            if (a < INT64_MIN / b) {
                return false;
            }
        } else {
            if (b == 0) {
                *result = 0;
                return true;
            }
            if (a < INT64_MAX / b) {
                return false;
            }
        }
    }
    
    *result = a * b;
    return true;
}

static bool safe_add_int64(int64_t a, int64_t b, int64_t *result) {
    if ((b > 0 && a > INT64_MAX - b) || (b < 0 && a < INT64_MIN - b)) {
        return false;
    }
    *result = a + b;
    return true;
}

static bool safe_sub_int64(int64_t a, int64_t b, int64_t *result) {
    if ((b > 0 && a < INT64_MIN + b) || (b < 0 && a > INT64_MAX + b)) {
        return false;
    }
    *result = a - b;
    return true;
}

static bool safe_div_int64(int64_t a, int64_t b, int64_t *result) {
    if (b == 0) {
        return false;
    }
    if (a == INT64_MIN && b == -1) {
        return false;
    }
    *result = a / b;
    return true;
}

static bool safe_mod_int64(int64_t a, int64_t b, int64_t *result) {
    if (b == 0) {
        return false;
    }
    if (a == INT64_MIN && b == -1) {
        *result = 0;
        return true;
    }
    *result = a % b;
    return true;
}

static bool extended_gcd(int64_t a, int64_t b, ExtendedGcdResult *result) {
    result->x = 0;
    result->y = 0;
    result->gcd = 0;
    
    int64_t old_r = a, r = b;
    int64_t old_s = 1, s = 0;
    int64_t old_t = 0, t = 1;
    
    while (r != 0) {
        int64_t quotient;
        if (!safe_div_int64(old_r, r, &quotient)) {
            return false;
        }
        
        int64_t temp_r = r;
        int64_t temp_s = s;
        int64_t temp_t = t;
        
        int64_t qr;
        if (!safe_mul_int64(quotient, r, &qr)) {
            return false;
        }
        if (!safe_sub_int64(old_r, qr, &r)) {
            return false;
        }
        
        int64_t qs;
        if (!safe_mul_int64(quotient, s, &qs)) {
            return false;
        }
        if (!safe_sub_int64(old_s, qs, &s)) {
            return false;
        }
        
        int64_t qt;
        if (!safe_mul_int64(quotient, t, &qt)) {
            return false;
        }
        if (!safe_sub_int64(old_t, qt, &t)) {
            return false;
        }
        
        old_r = temp_r;
        old_s = temp_s;
        old_t = temp_t;
    }
    
    result->x = old_s;
    result->y = old_t;
    result->gcd = old_r;
    
    if (result->gcd < 0) {
        if (result->gcd == INT64_MIN) {
            return false;
        }
        result->gcd = -result->gcd;
        
        if (result->x == INT64_MIN || result->y == INT64_MIN) {
            return false;
        }
        result->x = -result->x;
        result->y = -result->y;
    }
    
    return true;
}

int solve_linear_diophantine(int64_t a, int64_t b, int64_t n, 
                             int64_t *x_out, int64_t *y_out) {
    if (x_out == NULL || y_out == NULL) {
        return -1;
    }
    
    if (a == 0 && b == 0) {
        if (n == 0) {
            *x_out = 0;
            *y_out = 0;
            return 0;
        }
        return -1;
    }
    
    ExtendedGcdResult eg;
    if (!extended_gcd(a, b, &eg)) {
        return -1;
    }
    
    if (eg.gcd == 0) {
        return -1;
    }
    
    int64_t remainder;
    if (!safe_mod_int64(n, eg.gcd, &remainder)) {
        return -1;
    }
    
    if (remainder != 0) {
        return -1;
    }
    
    int64_t factor;
    if (!safe_div_int64(n, eg.gcd, &factor)) {
        return -1;
    }
    
    if (!safe_mul_int64(eg.x, factor, x_out)) {
        return -1;
    }
    
    if (!safe_mul_int64(eg.y, factor, y_out)) {
        return -1;
    }
    
    return 0;
}

static bool verify_solution(int64_t a, int64_t x, int64_t b, int64_t y, int64_t n) {
    int64_t ax, by, sum;
    
    if (!safe_mul_int64(a, x, &ax)) {
        return false;
    }
    
    if (!safe_mul_int64(b, y, &by)) {
        return false;
    }
    
    if (!safe_add_int64(ax, by, &sum)) {
        return false;
    }
    
    return sum == n;
}

static bool read_int64(const char *prompt, int64_t *value) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    size_t len;
    
    if (prompt == NULL || value == NULL) {
        return false;
    }
    
    printf("%s", prompt);
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len == 0) {
        return false;
    }
    
    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        return false;
    }
    
    errno = 0;
    *value = strtoimax(buffer, &endptr, 10);
    
    if (errno == ERANGE) {
        return false;
    }
    
    if (endptr == buffer) {
        return false;
    }
    
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }
    
    if (*endptr != '\0') {
        return false;
    }
    
    return true;
}

int main(void) {
    int64_t a, b, n;
    int64_t x, y;
    
    if (!read_int64("Enter coefficient a: ", &a)) {
        fprintf(stderr, "Invalid input for a\n");
        return EXIT_FAILURE;
    }
    
    if (!read_int64("Enter coefficient b: ", &b)) {
        fprintf(stderr, "Invalid input for b\n");
        return EXIT_FAILURE;
    }
    
    if (!read_int64("Enter constant n: ", &n)) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }
    
    if (solve_linear_diophantine(a, b, n, &x, &y) == 0) {
        printf("Solution: x = %" PRId64 ", y = %" PRId64 "\n", x, y);
        
        if (verify_solution(a, x, b, y, n)) {
            printf("Verification: %" PRId64 " * %" PRId64 " + %" PRId64 " * %" PRId64 " = %" PRId64 "\n", 
                   a, x, b, y, n);
        } else {
            printf("Verification: arithmetic overflow prevented verification\n");
        }
    } else {
        printf("No integer solution exists\n");
    }
    
    return EXIT_SUCCESS;
}
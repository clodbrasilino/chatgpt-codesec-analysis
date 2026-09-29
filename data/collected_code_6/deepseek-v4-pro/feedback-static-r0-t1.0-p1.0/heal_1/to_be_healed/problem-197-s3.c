#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

typedef struct {
    int base;
    int exponent;
} Tuple;

typedef struct {
    int base_result;
    int exponent_result;
} TupleResult;

static int safe_multiply(int a, int b) {
    /* Possible weaknesses found:
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'INT_MAX'
     */
    if (a > 0 && b > 0 && a > (INT_MAX / b)) return -1;
    /* Possible weaknesses found:
     *  'INT_MIN' undeclared (first use in this function)
     *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  use of undeclared identifier 'INT_MIN'
     */
    if (a > 0 && b < 0 && b < (INT_MIN / a)) return -1;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MIN'
     */
    if (a < 0 && b > 0 && a < (INT_MIN / b)) return -1;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     */
    if (a < 0 && b < 0 && a < (INT_MAX / b)) return -1;
    return a * b;
}

static int int_power(int base, int exp, int *overflow) {
    long long result = 1;
    long long b = base;
    int e = exp;

    if (e < 0) {
        if (base == 0) {
            *overflow = 1;
            return 0;
        }
        *overflow = 0;
        return 0;
    }

    while (e > 0) {
        if (e & 1) {
            result *= b;
            /* Possible weaknesses found:
             *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
             *  'INT_MAX' undeclared (first use in this function)
             *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
             *  use of undeclared identifier 'INT_MIN'
             *  'INT_MIN' undeclared (first use in this function)
             *  use of undeclared identifier 'INT_MAX'
             */
            if (result > INT_MAX || result < INT_MIN) {
                *overflow = 1;
                return 0;
            }
        }
        e >>= 1;
        if (e > 0) {
            b *= b;
            /* Possible weaknesses found:
             *  use of undeclared identifier 'INT_MIN'
             *  use of undeclared identifier 'INT_MAX'
             */
            if (b > INT_MAX || b < INT_MIN) {
                *overflow = 1;
                return 0;
            }
        }
    }

    *overflow = 0;
    return (int)result;
}

static int tuple_exponentiate(Tuple a, Tuple b, TupleResult *result) {
    int overflow = 0;
    int pow_a = int_power(a.base, a.exponent, &overflow);
    if (overflow) return 0;

    int pow_b = int_power(b.base, b.exponent, &overflow);
    if (overflow) return 0;

    int combined_exp = safe_multiply(a.exponent, b.exponent);
    if (combined_exp == -1 && a.exponent != 0 && b.exponent != 0) return 0;

    int final_base = safe_multiply(pow_a, pow_b);
    if (final_base == -1 && pow_a != 0 && pow_b != 0) return 0;

    result->base_result = final_base;
    result->exponent_result = combined_exp;

    return 1;
}

int main(void) {
    Tuple t1 = {2, 3};
    Tuple t2 = {3, 2};
    TupleResult result;

    if (tuple_exponentiate(t1, t2, &result)) {
        printf("%d %d\n", result.base_result, result.exponent_result);
    } else {
        printf("overflow\n");
    }

    Tuple t3 = {0, -1};
    Tuple t4 = {1, 1};

    if (tuple_exponentiate(t3, t4, &result)) {
        printf("%d %d\n", result.base_result, result.exponent_result);
    } else {
        printf("overflow\n");
    }

    Tuple t5 = {5, 10};
    Tuple t6 = {7, 8};

    if (tuple_exponentiate(t5, t6, &result)) {
        printf("%d %d\n", result.base_result, result.exponent_result);
    } else {
        printf("overflow\n");
    }

    return 0;
}
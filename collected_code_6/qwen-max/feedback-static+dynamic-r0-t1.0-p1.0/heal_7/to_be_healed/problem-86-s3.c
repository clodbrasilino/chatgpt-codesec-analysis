#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

bool is_safe_multiply(int64_t a, int64_t b, int64_t *result) {
    if (a > 0 && b > 0 && a > INT64_MAX / b) return false;
    /* Possible weaknesses found:
     *  Assuming that condition 'b<0' is not redundant
     *  Expression 'b' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation. [signConversionCond]
     *  Negative value is converted to an unsigned value
     */
    if (a < 0 && b < 0 && a < INT64_MIN / b) return false;
    /* Possible weaknesses found:
     *  Assuming that condition 'b<0' is not redundant
     *  Expression 'b' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation. [signConversionCond]
     *  Negative value is converted to an unsigned value
     */
    if (a > 0 && b < 0 && a > INT64_MIN / b) return false;
    if (a < 0 && b > 0 && a < INT64_MAX / b) return false;
    *result = a * b;
    return true;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 217, got 216
  *  test case 0 failed: expected 271, got 270
  *  test case 1 failed: expected 7, got 6
  */

int64_t nth_centered_hexagonal_number(int64_t n) {
    if (n > (INT64_MAX - 1) / 3 + 1 || n < 1) {
        fprintf(stderr, "Input value out of valid range for int64_t.\n");
        return -1;
    }
    if (n == 1) {
        return 1;
    }
    int64_t temp;
    if (!is_safe_multiply(3, n, &temp)) {
        fprintf(stderr, "Overflow detected.\n");
        return -1;
    }
    int64_t result;
    if (!is_safe_multiply(temp, n - 1, &result) || !is_safe_multiply(result, 1, &result)) {
        fprintf(stderr, "Overflow detected.\n");
        return -1;
    }
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%" SCNd64, &n) != 1 || n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    int64_t result = nth_centered_hexagonal_number(n);
    if (result == -1) {
        return 1;
    }
    printf("The %" PRIu64 "th centered hexagonal number is: %" PRIu64 "\n", n, result);
    return 0;
}
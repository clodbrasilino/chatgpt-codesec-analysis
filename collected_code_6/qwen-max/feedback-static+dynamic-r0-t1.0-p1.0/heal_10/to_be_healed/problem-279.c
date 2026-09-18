#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

/* Possible weaknesses found:
 *  unknown type name 'int62_t'; did you mean 'int64_t'?
 *  unknown type name 'int62_t'
 */
int64_t nth_decagonal_number(int62_t n) {
    if (n > 0 && n <= 2305843009213693951LL) {
        int64_t max_val = (LLONG_MAX - 3 * n) / 4;
        if (n > max_val || n * n > max_val) {
            return 0;
        }
        int64_t temp1 = 4 * n;
        int64_t temp2 = n * n;
        if (temp1 > LLONG_MAX / n || temp2 > LLONG_MAX / 4) {
            return 0;
        }
        int64_t result = 4 * temp2 - 3 * n;
        return result;
    }
    return 0;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%" SCNd64, &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    /* Possible weaknesses found:
     *  implicit declaration of function 'nth_decagonal_number' [-Wimplicit-function-declaration]
     */
    int64_t result = nth_decagonal_number(n);
    if (result == 0) {
        fprintf(stderr, "Input too large for computation\n");
        return 1;
    }
    printf("The %" PRId64 "th decagonal number is: %" PRId64 "\n", n, result);
    return 0;
}
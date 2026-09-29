#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  'SCNd64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
  */

int64_t nth_rectangular_number(int64_t n) {
    int64_t result = n * (n + 1);
    if (result / n != n + 1) {
        fprintf(stderr, "Overflow detected\n");
        return -1;
    }
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  expected ')'
     *  to match this '('
     *  expected ')' before 'SCNd64'
     */
    if (scanf("%" SCNd64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n < 1) {
        fprintf(stderr, "n must be a positive integer\n");
        return 1;
    }
    int64_t result = nth_rectangular_number(n);
    if (result == -1) {
        return 1;
    }
    printf("The %ld-th rectangular number is: %ld\n", n, result);
    return 0;
}
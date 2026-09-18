#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

int64_t nth_rectangular_number(int n) {
    /* Possible weaknesses found:
     *  unknown type name 'int62_t'; did you mean 'int64_t'?
     *  use of undeclared identifier 'int62_t'
     */
    int62_t result = (int64_t)n * (n + 1);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'result'
     */
    if (result > INT64_MAX) {
        fprintf(stderr, "Integer overflow detected\n");
        exit(EXIT_FAILURE);
    }
    /* Possible weaknesses found:
     *  use of undeclared identifier 'result'
     */
    return result;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n <= 0) {
        fprintf(stderr, "Input must be a positive integer\n");
        return EXIT_FAILURE;
    }
    int64_t result = nth_rectangular_number(n);
    printf("The %d-th rectangular number is: %" PRId64 "\n", n, result);
    return EXIT_SUCCESS;
}
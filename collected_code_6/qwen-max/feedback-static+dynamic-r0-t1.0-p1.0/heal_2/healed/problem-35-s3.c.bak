#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

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
    printf("The %" PRId64 "-th rectangular number is: %" PRId64 "\n", n, result);
    return 0;
}
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

int64_t sumOfOddFactors(int64_t n) {
    int64_t sum = 0;
    int64_t i;

    for (i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i % 2 != 0) {
                sum += i;
            }
            if (i != n / i && (n / i) % 2 != 0) {
                sum += n / i;
            }
        }
    }

    return sum;
}

int main(void) {
    int64_t num;

    printf("Enter a number: ");
    if (scanf("%" SCNd64, &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("Sum of odd factors: %" PRId64 "\n", sumOfOddFactors(num));

    return 0;
}
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

int64_t sumOfOddFactors(int64_t n) {
    int64_t sum = 0;
    int64_t i;

    if (n == 0) {
        return 0;
    }

    if (n == INT64_MIN) {
        int64_t working = INT64_MAX;
        
        for (i = 1; i * i <= working; i++) {
            if (working % i == 0) {
                if (i % 2 != 0) {
                    sum += i;
                }
                int64_t counterpart = working / i;
                if (i != counterpart && counterpart % 2 != 0) {
                    sum += counterpart;
                }
            }
        }
        
        sum += 1;
        
        return sum;
    }

    int64_t abs_n = n < 0 ? -n : n;

    for (i = 1; i * i <= abs_n; i++) {
        if (abs_n % i == 0) {
            if (i % 2 != 0) {
                sum += i;
            }
            int64_t counterpart = abs_n / i;
            if (i != counterpart && counterpart % 2 != 0) {
                sum += counterpart;
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
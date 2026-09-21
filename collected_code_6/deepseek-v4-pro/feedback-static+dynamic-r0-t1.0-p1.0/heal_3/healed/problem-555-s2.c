#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int64_t sum_of_cubes_minus_sum(int64_t n) {
    if (n < 1) {
        return 0;
    }
    
    if (n > 28782) {
        return -1;
    }
    
    int64_t sum, sum_cubes;
    
    if (n > 28782) {
        return -1;
    }
    
    if (n % 2 == 0) {
        int64_t half_n = n / 2;
        if (half_n > INT64_MAX / (n + 1)) {
            return -1;
        }
        sum = half_n * (n + 1);
    } else {
        int64_t half_n_plus_1 = (n + 1) / 2;
        if (half_n_plus_1 > INT64_MAX / n) {
            return -1;
        }
        sum = n * half_n_plus_1;
    }
    
    if (sum > INT64_MAX / sum) {
        return -1;
    }
    sum_cubes = sum * sum;
    
    if (sum_cubes < sum) {
        return -1;
    }
    
    return sum_cubes - sum;
}

int main(void) {
    char buffer[32];
    int64_t n;
    
    printf("Enter a positive integer: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }
    
    char *endptr;
    errno = 0;
    int64_t val = strtoll(buffer, &endptr, 10);
    
    if (errno == ERANGE || val > INT64_MAX || val < 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (endptr == buffer || *endptr != '\n') {
        printf("Invalid input\n");
        return 1;
    }
    
    n = val;
    
    int64_t result = sum_of_cubes_minus_sum(n);
    if (result == -1 && n > 28782) {
        printf("Overflow detected\n");
        return 1;
    }
    
    printf("%" PRId64 "\n", result);
    return 0;
}
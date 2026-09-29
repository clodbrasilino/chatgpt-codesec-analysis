#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

int64_t compute_difference(int64_t n) {
    if (n < 0) {
        return -1;
    }
    
    if (n == 0) {
        return 0;
    }
    
    if (n > 3037000499LL) {
        return -1;
    }
    
    int64_t sum;
    if (n % 2 == 0) {
        if (n > INT64_MAX / ((n + 1) / 2)) {
            return -1;
        }
        sum = n / 2 * (n + 1);
    } else {
        if (n > INT64_MAX / ((n + 1) / 2)) {
            return -1;
        }
        sum = n * ((n + 1) / 2);
    }
    
    if (sum > INT64_MAX / sum) {
        return -1;
    }
    
    int64_t sum_of_cubes = sum * sum;
    
    if (sum_of_cubes < sum) {
        return -1;
    }
    
    return sum_of_cubes - sum;
}

int main(void) {
    int64_t n;
    if (scanf("%" SCNd64, &n) != 1) {
        return 1;
    }
    printf("%" PRId64 "\n", compute_difference(n));
    return 0;
}
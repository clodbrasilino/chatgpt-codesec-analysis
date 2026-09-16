#include <stdio.h>
#include <stdint.h>

uint64_t count_squares(int64_t m, int64_t n);

uint64_t count_squares(int64_t m, int64_t n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }

    uint64_t total_squares = 0;
    int64_t min_dim = (m < n) ? m : n;

    for (int64_t k = 1; k <= min_dim; ++k) {
        total_squares += (uint64_t)(m - k + 1) * (uint64_t)(n - k + 1);
    }

    return total_squares;
}

int main(void) {
    int64_t m = 4;
    int64_t n = 3;
    
    uint64_t squares = count_squares(m, n);
    
    if (squares > 0) {
        printf("%llu\n", (unsigned long long)squares);
    } else {
        printf("Invalid dimensions provided.\n");
    }

    return 0;
}
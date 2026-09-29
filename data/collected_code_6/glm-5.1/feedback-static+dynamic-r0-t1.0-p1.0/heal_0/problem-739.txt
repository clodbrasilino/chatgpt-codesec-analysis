#include <stdio.h>
#include <math.h>
#include <limits.h>

unsigned long long find_smallest_triangular_index(int n) {
    if (n <= 0) {
        return 0;
    }

    unsigned long long bound = 1;
    for (int i = 1; i < n; i++) {
        bound *= 10;
        if (bound == 0) {
            return 0;
        }
    }

    unsigned long long i = 1;
    unsigned long long tri = 1;

    while (1) {
        if (tri >= bound) {
            return i;
        }

        unsigned long long next_i = i + 1;
        if (next_i > ULLONG_MAX / i || next_i * i > ULLONG_MAX / 2ULL) {
            return 0;
        }

        tri = tri + next_i;
        i = next_i;
    }
}

int main(void) {
    int n;

    if (scanf("%d", &n) != 1) {
        return 1;
    }

    unsigned long long result = find_smallest_triangular_index(n);

    if (result == 0) {
        return 1;
    }

    printf("%llu\n", result);

    return 0;
}
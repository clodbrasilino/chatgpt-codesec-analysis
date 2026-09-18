#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_series(int64_t n) {
    if (n <= 0) {
        return 0;
    }
    if (n % 2 == 0) {
        return (n / 2) * (n + 1);
    } else {
        return n * ((n + 1) / 2);
    }
}

int64_t sum_triangular(int64_t n) {
    if (n <= 0) {
        return 0;
    }
    if (n % 2 == 0) {
        return n / 2 * (n + 1) * (n + 2) / 3;
    } else {
        return n * ((n + 1) / 2) * (n + 2) / 3;
    }
}

int64_t countTriangles(int n) {
    if (n <= 0) {
        return 0;
    }

    int64_t up = sum_triangular(n);

    int64_t m = (n - 1) / 2;
    int64_t down = m * (m + 1) * (4 * m + 5) / 6;

    int64_t both = 0;
    if (n >= 4) {
        int64_t k = (n - 3) / 2;
        int64_t sum1 = sum_series(k);
        int64_t sum2 = k * (k + 1) * (2 * k + 1) / 6;
        int64_t sum_tri = (sum1 + sum2) / 2;
        both = 2 * sum_tri;
    }

    return up + down + both;
}

int main(void) {
    int n;

    printf("Enter side length: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Side length must be non-negative\n");
        return EXIT_FAILURE;
    }

    int64_t result = countTriangles(n);
    printf("Maximum equilateral triangles: %" PRId64 "\n", result);

    return EXIT_SUCCESS;
}
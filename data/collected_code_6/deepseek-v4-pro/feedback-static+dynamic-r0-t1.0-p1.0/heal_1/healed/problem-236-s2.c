#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t countTriangles(int n) {
    if (n <= 0) {
        return 0;
    }

    int64_t up = 0;
    for (int i = 1; i <= n; i++) {
        up += (int64_t)i * (i + 1) / 2;
    }

    int64_t down = 0;
    for (int i = n - 1; i > 0; i -= 2) {
        down += (int64_t)i * (i + 1) / 2;
    }

    int64_t both = 0;
    if (n >= 4) {
        for (int i = n - 3; i > 0; i -= 2) {
            both += (int64_t)i * (i + 1) / 2;
        }
        both = both * 2;
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

    printf("Maximum equilateral triangles: %" PRId64 "\n", countTriangles(n));

    return EXIT_SUCCESS;
}
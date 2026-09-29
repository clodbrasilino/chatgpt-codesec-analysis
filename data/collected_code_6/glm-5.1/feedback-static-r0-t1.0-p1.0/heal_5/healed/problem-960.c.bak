#include <stdio.h>
#include <stdlib.h>

int tiling_ways(int n) {
    if (n < 0) {
        return 0;
    }
    if (n <= 2) {
        return n == 0 ? 1 : n;
    }
    int a = 1, b = 2, c;
    for (int i = 3; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char const * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    int ways = tiling_ways(n);
    printf("%d\n", ways);
    return EXIT_SUCCESS;
}
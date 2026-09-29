#include <stdio.h>
#include <stdlib.h>

long long count_cubes(int n, int k) {
    if (n < k || k <= 0) {
        return 0;
    }
    long long diff = (long long)n - k;
    return diff * diff * diff;
}

int main(void) {
    int n, k;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    printf("Enter k: ");
    if (scanf("%d", &k) != 1) {
        return EXIT_FAILURE;
    }
    if (n < 0 || k <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", count_cubes(n, k));
    return EXIT_SUCCESS;
}
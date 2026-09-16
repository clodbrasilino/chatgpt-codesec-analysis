#include <stdio.h>
#include <stdlib.h>

int find_largest_k(int x, int y) {
    if (x <= 0 || y < 0 || y >= x) {
        return -1;
    }
    long long k = (long long)(~0ULL) / x * x + y;
    return (k % x == y) ? k : -1;
}

int main() {
    int x, y;
    printf("Enter x and y: ");
    if (scanf("%d %d", &x, &y) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int result = find_largest_k(x, y);
    if (result == -1) {
        printf("No valid k found\n");
    } else {
        printf("Largest k: %lld\n", (long long)result);
    }
    return 0;
}
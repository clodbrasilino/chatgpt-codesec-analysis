#include <stdio.h>
#include <stdlib.h>

unsigned long long find_ways(int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    unsigned long long a = 1, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + 2 * b;
        a = b;
        b = c;
    }
    return c;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n < 0) {
        fprintf(stderr, "Value must be non-negative\n");
        return EXIT_FAILURE;
    }
    unsigned long long ways = find_ways(n);
    printf("Number of ways to fill a 3x%d board with 2x1 dominoes: %llu\n", n, ways);
    return 0;
}
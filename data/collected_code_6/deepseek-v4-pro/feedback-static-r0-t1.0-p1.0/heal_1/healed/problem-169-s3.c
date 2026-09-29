#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long pell_number(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: negative input\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0) return 0;
    if (n == 1) return 1;

    unsigned long long prev2 = 0;
    unsigned long long prev1 = 1;
    unsigned long long current = 0;

    for (int i = 2; i <= n; i++) {
        if (prev1 > (ULLONG_MAX - 2 * prev2)) {
            fprintf(stderr, "Error: overflow\n");
            exit(EXIT_FAILURE);
        }
        current = 2 * prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = pell_number(n);
    printf("Pell(%d) = %llu\n", n, result);

    return 0;
}
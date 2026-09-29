#include <stdio.h>
#include <stdlib.h>

unsigned long long lucas(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: Input must be non-negative.\n");
        exit(EXIT_FAILURE);
    }

    if (n == 0) return 2;
    if (n == 1) return 1;

    unsigned long long a = 2, b = 1, result = 0;
    for (int i = 2; i <= n; i++) {
        result = a + b;
        a = b;
        b = result;
    }
    return result;
}

int main(void) {
    int n;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = lucas(n);
    printf("Lucas number L%d = %llu\n", n, result);

    return EXIT_SUCCESS;
}
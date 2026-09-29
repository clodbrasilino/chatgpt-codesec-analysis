#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

unsigned long long bellNumber(int n) {
    if (n < 0) return 0;
    unsigned long long *bell = (unsigned long long *)calloc((n+1)*(n+1), sizeof(unsigned long long));
    if (bell == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    bell[0] = 1;
    for (int i = 1; i <= n; i++) {
        bell[i*(n+1)] = bell[(i-1)*(n+1)+(i-1)];
        for (int j = 1; j <= i; j++)
            bell[i*(n+1)+j] = bell[(i-1)*(n+1)+(j-1)] + bell[i*(n+1)+(j-1)];
    }
    unsigned long long result = bell[n*(n+1)];
    free(bell);
    return result;
}

int main() {
    char input[16];
    fgets(input, sizeof(input), stdin);
    int n;
    if (sscanf(input, "%d", &n) != 1 || n < 0 || n > INT_MAX / 2) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    unsigned long long result = bellNumber(n);
    printf("The %dth Bell number is: %llu\n", n, result);
    return EXIT_SUCCESS;
}
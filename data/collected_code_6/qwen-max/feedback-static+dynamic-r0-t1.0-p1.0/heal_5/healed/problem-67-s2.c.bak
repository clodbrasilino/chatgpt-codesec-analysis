#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

unsigned long long bell_number(int n) {
    unsigned long long **bell = (unsigned long long **)calloc(n+1, sizeof(unsigned long long *));
    if (bell == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= n; i++) {
        bell[i] = (unsigned long long *)calloc(n+1, sizeof(unsigned long long));
        if (bell[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(bell[j]);
            }
            free(bell);
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    bell[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        bell[i][0] = bell[i-1][i-1];
        for (int j = 1; j <= i; j++)
            bell[i][j] = (bell[i-1][j-1] + bell[i][j-1]) % 18446744073709551615ULL;
    }
    unsigned long long result = bell[n][0];
    for (int i = 0; i <= n; i++) {
        free(bell[i]);
    }
    free(bell);
    return result;
}

int main() {
    int n;
    printf("Enter the number of elements in the set: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n < 0) {
        fprintf(stderr, "Number of elements must be non-negative\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = bell_number(n);
    printf("The number of ways to partition a set of %d elements is: %" PRIu64 "\n", n, result);

    return EXIT_SUCCESS;
}
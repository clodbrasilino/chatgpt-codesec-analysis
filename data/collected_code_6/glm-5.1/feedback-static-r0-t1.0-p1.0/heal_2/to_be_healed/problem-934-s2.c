#include <stdio.h>
#include <stdlib.h>

unsigned long long delannoy(int n) {
    if (n < 0) {
        return 0;
    }
    unsigned long long **d = (unsigned long long **)malloc((n + 1) * sizeof(unsigned long long *));
    if (d == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= n; i++) {
        d[i] = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
        if (d[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(d[j]);
            }
            free(d);
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i <= n; i++) {
        d[0][i] = 1;
        d[i][0] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            d[i][j] = d[i - 1][j] + d[i][j - 1] + d[i - 1][j - 1];
        }
    }
    unsigned long long result = d[n][n];
    for (int i = 0; i <= n; i++) {
        free(d[i]);
    }
    free(d);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 20) {
        fprintf(stderr, "Input out of bounds. 0 <= n <= 20\n");
        return EXIT_FAILURE;
    }
    int n = (int)val;
    printf("%llu\n", delannoy(n));
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

unsigned long long delannoy(int n) {
    if (n < 0) {
        return 0;
    }
    unsigned long long *d = malloc((n + 1) * sizeof(unsigned long long));
    if (d == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= n; i++) {
        d[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        unsigned long long prev = d[0];
        for (int j = 1; j <= n; j++) {
            unsigned long long temp = d[j];
            d[j] = d[j] + d[j - 1] + prev;
            prev = temp;
        }
    }
    unsigned long long result = d[n];
    free(d);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    if (n < 0 || n > 20) {
        fprintf(stderr, "Input out of bounds. 0 <= n <= 20\n");
        return EXIT_FAILURE;
    }
    printf("%llu\n", delannoy(n));
    return EXIT_SUCCESS;
}
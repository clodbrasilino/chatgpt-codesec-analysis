#include <stdio.h>
#include <stdlib.h>

unsigned long long find_lucas(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }

    unsigned long long prev2 = 2;
    unsigned long long prev1 = 1;
    unsigned long long current = 0;

    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val < 0 || val > 92) {
        fprintf(stderr, "Error: n must be a non-negative integer up to 92.\n");
        return 1;
    }

    unsigned long long result = find_lucas((int)val);
    printf("%llu\n", result);

    return 0;
}
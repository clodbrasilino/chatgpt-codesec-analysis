#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int calculate_bell_number(int n, unsigned long long *result) {
    if (result == NULL) {
        return -1;
    }
    if (n < 0) {
        return -1;
    }
    if (n > 26) {
        return -1;
    }

    unsigned long long *bell = (unsigned long long *)malloc((size_t)(n + 1) * sizeof(unsigned long long));
    if (bell == NULL) {
        return -1;
    }

    bell[0] = 1;

    for (int i = 1; i <= n; i++) {
        bell[i] = 0;
        for (int j = 0; j < i; j++) {
            unsigned long long binomial = 1;
            for (int k = 0; k < j; k++) {
                if (binomial > ULLONG_MAX / (unsigned long long)(i - 1 - k)) {
                    free(bell);
                    return -1;
                }
                binomial = binomial * (unsigned long long)(i - 1 - k) / (unsigned long long)(k + 1);
            }
            if (bell[i] > ULLONG_MAX - binomial * bell[i - 1 - j]) {
                free(bell);
                return -1;
            }
            bell[i] += binomial * bell[i - 1 - j];
        }
    }

    *result = bell[n];
    free(bell);
    return 0;
}

int main(void) {
    int n;
    unsigned long long result;

    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (calculate_bell_number(n, &result) != 0) {
        return 1;
    }

    printf("%llu\n", result);
    return 0;
}
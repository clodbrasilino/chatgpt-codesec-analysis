#include <stdio.h>
#include <stdlib.h>

unsigned long long findNthBellNumber(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0 || n == 1) {
        return 1;
    }

    unsigned long long *bell = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (bell == NULL) {
        exit(EXIT_FAILURE);
    }

    bell[0] = 1;

    for (int i = 1; i < n; i++) {
        unsigned long long prev = bell[0];
        bell[0] = bell[i - 1];

        for (int j = 1; j <= i; j++) {
            unsigned long long curr = bell[j];
            bell[j] = prev + bell[j - 1];
            prev = curr;
        }
    }

    unsigned long long result = bell[n - 1];
    free(bell);
    bell = NULL;

    return result;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        return EXIT_FAILURE;
    }

    unsigned long long result = findNthBellNumber(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}
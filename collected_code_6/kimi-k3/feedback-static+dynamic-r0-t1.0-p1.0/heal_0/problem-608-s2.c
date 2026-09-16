#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long bell_number(int n)
{
    if (n < 0)
        return 0;

    unsigned long long *bell = calloc((size_t)n + 1, sizeof(unsigned long long));
    if (bell == NULL)
        return 0;

    bell[0] = 1;

    for (int i = 1; i <= n; i++) {
        bell[i] = bell[i - 1];
        for (int j = i - 1; j >= 1; j--) {
            if (bell[j] > ULLONG_MAX - bell[j - 1]) {
                free(bell);
                return 0;
            }
            bell[j] += bell[j - 1];
        }
    }

    unsigned long long result = bell[n];
    free(bell);
    return result;
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = bell_number(n);
    if (result == 0 && n != 0) {
        fprintf(stderr, "Overflow or allocation error\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);
    return EXIT_SUCCESS;
}
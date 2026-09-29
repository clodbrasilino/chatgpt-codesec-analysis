#include <stdio.h>
#include <stdlib.h>

unsigned long long delannoy(int m, int n) {
    unsigned long long *prev = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    unsigned long long *curr = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    unsigned long long *temp = NULL;
    int i, j;

    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        return 0;
    }

    for (j = 0; j <= n; j++) {
        prev[j] = 1;
    }

    for (i = 1; i <= m; i++) {
        curr[0] = 1;
        for (j = 1; j <= n; j++) {
            curr[j] = prev[j] + prev[j - 1] + curr[j - 1];
        }
        temp = prev;
        prev = curr;
        curr = temp;
    }

    {
        unsigned long long result = prev[n];
        free(prev);
        free(curr);
        return result;
    }
}

int main(void) {
    int m, n;
    unsigned long long result;

    if (scanf("%d %d", &m, &n) != 2 || m < 0 || n < 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    result = delannoy(m, n);
    printf("%llu\n", result);

    return 0;
}
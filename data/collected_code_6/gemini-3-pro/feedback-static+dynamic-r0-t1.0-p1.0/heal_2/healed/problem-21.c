#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int* find_multiples(int n, int m) {
    if (m <= 0 || (size_t)m > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int* multiples = (int*)malloc((size_t)m * sizeof(int));
    if (multiples == NULL) {
        return NULL;
    }

    for (int i = 0; i < m; i++) {
        long long val = (long long)n * (i + 1);
        if (val > INT_MAX || val < INT_MIN) {
            free(multiples);
            return NULL;
        }
        multiples[i] = (int)val;
    }

    return multiples;
}

int main(void) {
    int n, m;

    if (scanf("%d %d", &n, &m) != 2) {
        return 1;
    }

    int* multiples = find_multiples(n, m);
    if (multiples == NULL) {
        return 1;
    }

    for (int i = 0; i < m; i++) {
        printf("%d ", multiples[i]);
    }
    printf("\n");

    free(multiples);

    return 0;
}
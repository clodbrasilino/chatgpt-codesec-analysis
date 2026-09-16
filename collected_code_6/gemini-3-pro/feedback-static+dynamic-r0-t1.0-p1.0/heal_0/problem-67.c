#include <stdio.h>
#include <stdlib.h>

int get_bell_number(unsigned int n, unsigned long long *result) {
    unsigned long long *prev = NULL;
    unsigned long long *curr = NULL;
    unsigned int i;
    unsigned int j;

    if (!result) {
        return -1;
    }
    
    if (n > 25) {
        return -1;
    }

    if (n == 0) {
        *result = 1;
        return 0;
    }

    prev = (unsigned long long *)malloc(sizeof(unsigned long long) * n);
    curr = (unsigned long long *)malloc(sizeof(unsigned long long) * n);
    
    if (!prev || !curr) {
        free(prev);
        free(curr);
        return -1;
    }

    prev[0] = 1;
    for (i = 1; i < n; i++) {
        curr[0] = prev[i - 1];
        for (j = 1; j <= i; j++) {
            curr[j] = prev[j - 1] + curr[j - 1];
        }
        for (j = 0; j <= i; j++) {
            prev[j] = curr[j];
        }
    }

    *result = prev[n - 1];
    
    free(prev);
    free(curr);

    return 0;
}

int main(void) {
    unsigned int n = 10;
    unsigned long long result = 0;

    if (get_bell_number(n, &result) == 0) {
        printf("%llu\n", result);
    } else {
        fprintf(stderr, "Error calculating Bell number.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
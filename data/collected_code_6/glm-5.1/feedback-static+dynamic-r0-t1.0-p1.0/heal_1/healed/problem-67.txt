#include <stdio.h>
#include <stdlib.h>

unsigned long long compute_bell(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    unsigned long long *prev = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    unsigned long long *curr = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        exit(EXIT_FAILURE);
    }
    prev[0] = 1;
    for (int i = 1; i <= n; i++) {
        curr[0] = prev[i - 1];
        for (int j = 1; j <= i; j++) {
            curr[j] = curr[j - 1] + prev[j - 1];
        }
        unsigned long long *temp = prev;
        prev = curr;
        curr = temp;
    }
    unsigned long long res = prev[0];
    free(prev);
    free(curr);
    return res;
}

int main(void) {
    printf("%llu\n", compute_bell(0));
    printf("%llu\n", compute_bell(1));
    printf("%llu\n", compute_bell(5));
    printf("%llu\n", compute_bell(50));
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

unsigned long long bell_number(int n) {
    if (n < 0) return 0;
    unsigned long long *prev = malloc((n + 2) * sizeof(unsigned long long));
    unsigned long long *curr = malloc((n + 2) * sizeof(unsigned long long));
    if (!prev || !curr) {
        free(prev);
        free(curr);
        return 0;
    }
    prev[0] = 1;
    for (int i = 1; i <= n; i++) {
        curr[0] = prev[i - 1];
        for (int j = 1; j <= i; j++) {
            curr[j] = curr[j - 1] + prev[j - 1];
        }
        unsigned long long *tmp = prev;
        prev = curr;
        curr = tmp;
    }
    unsigned long long result = prev[n];
    free(prev);
    free(curr);
    return result;
}

int main(void) {
    printf("%llu\n", bell_number(0));
    printf("%llu\n", bell_number(1));
    printf("%llu\n", bell_number(10));
    return 0;
}
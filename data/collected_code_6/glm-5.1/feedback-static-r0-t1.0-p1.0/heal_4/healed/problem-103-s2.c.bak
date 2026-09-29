#include <stdio.h>
#include <stdlib.h>

long long eulerian_number(int n, int m) {
    if (n < 0 || m < 0 || m >= n) {
        return 0;
    }
    if (m == 0) {
        return 1;
    }
    long long *prev = (long long *)calloc(m + 1, sizeof(long long));
    long long *curr = (long long *)calloc(m + 1, sizeof(long long));
    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        return -1;
    }
    prev[0] = 1;
    for (int i = 2; i <= n; i++) {
        curr[0] = 1;
        for (int j = 1; j <= m && j < i; j++) {
            curr[j] = (long long)(i - j) * prev[j - 1] + (long long)(j + 1) * prev[j];
        }
        long long *temp = prev;
        prev = curr;
        curr = temp;
    }
    long long result = prev[m];
    free(prev);
    free(curr);
    return result;
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        return 1;
    }
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    long long result = eulerian_number(n, m);
    if (result == -1) {
        return 1;
    }
    printf("%lld\n", result);
    return 0;
}
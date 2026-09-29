#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long eulerian_number(int n, int m) {
    if (n < 0 || m < 0 || m >= n) {
        return 0;
    }
    
    if (m == 0) {
        return 1;
    }
    
    unsigned long long *prev = (unsigned long long *)calloc(m + 1, sizeof(unsigned long long));
    unsigned long long *curr = (unsigned long long *)calloc(m + 1, sizeof(unsigned long long));
    
    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        return ULLONG_MAX;
    }
    
    prev[0] = 1;
    
    for (int i = 2; i <= n; i++) {
        curr[0] = 1;
        for (int j = 1; j < i && j <= m; j++) {
            if (prev[j - 1] > ULLONG_MAX - (unsigned long long)(i - j) * prev[j] ||
                prev[j] > ULLONG_MAX / (unsigned long long)(i - j)) {
                free(prev);
                free(curr);
                return ULLONG_MAX;
            }
            curr[j] = (i - j) * prev[j] + (j + 1) * prev[j - 1];
        }
        unsigned long long *temp = prev;
        prev = curr;
        curr = temp;
    }
    
    unsigned long long result = prev[m];
    free(prev);
    free(curr);
    
    return result;
}

int main(void) {
    int n = 10;
    int m = 4;
    
    unsigned long long res = eulerian_number(n, m);
    if (res == ULLONG_MAX) {
        return 1;
    }
    
    printf("%llu\n", res);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

unsigned long long eulerian(int n, int m) {
    if (n <= 0 || m < 0 || m >= n) {
        return 0;
    }
    
    unsigned long long *prev = (unsigned long long *)calloc((size_t)n, sizeof(unsigned long long));
    unsigned long long *curr = (unsigned long long *)calloc((size_t)n, sizeof(unsigned long long));
    
    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        return 0;
    }
    
    prev[0] = 1;
    
    for (int i = 2; i <= n; i++) {
        curr[0] = 1;
        for (int j = 1; j < i - 1; j++) {
            curr[j] = (unsigned long long)(j + 1) * prev[j] + (unsigned long long)(i - j) * prev[j - 1];
        }
        curr[i - 1] = 1;
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
    int n, m;
    
    if (scanf("%d %d", &n, &m) != 2) {
        return 1;
    }
    
    unsigned long long result = eulerian(n, m);
    printf("%llu\n", result);
    fflush(stdout);
    
    return 0;
}
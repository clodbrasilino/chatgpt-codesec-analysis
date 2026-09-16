#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

unsigned long long eulerian_number(int n, int m) {
    if (n <= 0 || m < 0 || m >= n) {
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
            unsigned long long term1;
            if ((i - j) > 0 && prev[j] > ULLONG_MAX / (unsigned long long)(i - j)) {
                free(prev);
                free(curr);
                return ULLONG_MAX;
            }
            term1 = (unsigned long long)(i - j) * prev[j];
            
            unsigned long long term2;
            if (prev[j - 1] > ULLONG_MAX / (unsigned long long)(j + 1)) {
                free(prev);
                free(curr);
                return ULLONG_MAX;
            }
            term2 = (unsigned long long)(j + 1) * prev[j - 1];
            
            if (term1 > ULLONG_MAX - term2) {
                free(prev);
                free(curr);
                return ULLONG_MAX;
            }
            curr[j] = term1 + term2;
        }
        unsigned long long *temp = prev;
        prev = curr;
        curr = temp;
        memset(curr, 0, (m + 1) * sizeof(unsigned long long));
    }
    
    unsigned long long result = prev[m];
    free(prev);
    free(curr);
    
    return result;
}

int main(void) {
    int test_cases[][2] = {{3, 1}, {4, 1}, {5, 2}};
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_cases; i++) {
        int n = test_cases[i][0];
        int m = test_cases[i][1];
        unsigned long long res = eulerian_number(n, m);
        if (res == ULLONG_MAX) {
            printf("Overflow\n");
        } else {
            printf("%llu\n", res);
        }
    }
    
    return 0;
}
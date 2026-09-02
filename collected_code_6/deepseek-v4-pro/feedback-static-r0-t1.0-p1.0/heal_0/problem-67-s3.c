#include <stdio.h>
#include <stdlib.h>

unsigned long long bell_number(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long **bell = (unsigned long long **)malloc((n + 1) * sizeof(unsigned long long *));
    if (!bell) {
        return 0;
    }
    
    for (int i = 0; i <= n; i++) {
        bell[i] = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
        if (!bell[i]) {
            for (int j = 0; j < i; j++) {
                free(bell[j]);
            }
            free(bell);
            return 0;
        }
    }
    
    bell[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        bell[i][0] = bell[i - 1][i - 1];
        for (int j = 1; j <= i; j++) {
            bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1];
        }
    }
    
    unsigned long long result = bell[n][0];
    
    for (int i = 0; i <= n; i++) {
        free(bell[i]);
    }
    free(bell);
    
    return result;
}

int main(void) {
    int test_cases[] = {0, 1, 2, 3, 4, 5, 10, 15, 20};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        unsigned long long result = bell_number(test_cases[i]);
        printf("Bell number B(%d) = %llu\n", test_cases[i], result);
    }
    
    return 0;
}
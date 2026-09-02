#include <stdio.h>
#include <stdlib.h>

long long** createBellTriangle(int n) {
    long long** bell = (long long**)malloc(n * sizeof(long long*));
    if (bell == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < n; i++) {
        bell[i] = (long long*)malloc(n * sizeof(long long));
        if (bell[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(bell[j]);
            }
            free(bell);
            return NULL;
        }
    }
    
    return bell;
}

void freeBellTriangle(long long** bell, int n) {
    if (bell == NULL) {
        return;
    }
    
    for (int i = 0; i < n; i++) {
        free(bell[i]);
    }
    free(bell);
}

long long nth_bell_number(int n) {
    if (n < 0) {
        return -1;
    }
    
    if (n == 0) {
        return 1;
    }
    
    long long** bell = createBellTriangle(n + 1);
    if (bell == NULL) {
        return -1;
    }
    
    bell[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        bell[i][0] = bell[i - 1][i - 1];
        
        for (int j = 1; j <= i; j++) {
            bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1];
        }
    }
    
    long long result = bell[n][0];
    freeBellTriangle(bell, n + 1);
    return result;
}

int main(void) {
    int test_values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (int i = 0; i < num_tests; i++) {
        long long result = nth_bell_number(test_values[i]);
        if (result != -1) {
            printf("Bell number B%d = %lld\n", test_values[i], result);
        } else {
            printf("Error calculating Bell number B%d\n", test_values[i]);
        }
    }
    
    return 0;
}
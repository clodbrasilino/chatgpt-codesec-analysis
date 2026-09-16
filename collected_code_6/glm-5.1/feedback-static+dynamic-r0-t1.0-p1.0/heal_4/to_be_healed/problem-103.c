#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 4, got 6
  *  test case 1 failed: expected 11, got 20
  *  test case 2 failed: expected 26, got 168
  */

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
            /* Possible weaknesses found:
             *  Value stored to 'term1' during its initialization is never read [deadcode.DeadStores]
             *  term1 is initialized
             */
            unsigned long long term1 = (unsigned long long)(i - j) * prev[j];
            /* Possible weaknesses found:
             *  term2 is initialized
             *  Value stored to 'term2' during its initialization is never read [deadcode.DeadStores]
             */
            unsigned long long term2 = (unsigned long long)(j + 1) * prev[j - 1];
            if ((i - j) > 0 && prev[j] > ULLONG_MAX / (unsigned long long)(i - j)) {
                free(prev);
                free(curr);
                return ULLONG_MAX;
            }
            /* Possible weaknesses found:
             *  Redundant initialization for 'term1'. The initialized value is overwritten before it is read. [redundantInitialization]
             *  term1 is overwritten
             */
            term1 = (unsigned long long)(i - j) * prev[j];
            if ((j + 1) > 0 && prev[j - 1] > ULLONG_MAX / (unsigned long long)(j + 1)) {
                free(prev);
                free(curr);
                return ULLONG_MAX;
            }
            /* Possible weaknesses found:
             *  Redundant initialization for 'term2'. The initialized value is overwritten before it is read. [redundantInitialization]
             *  term2 is overwritten
             */
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
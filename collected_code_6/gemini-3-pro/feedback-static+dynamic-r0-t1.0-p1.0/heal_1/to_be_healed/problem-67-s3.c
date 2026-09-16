#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 6775685320645824322581483068371419745979053216268760300, got -8539980777762638612
  */

unsigned long long bell_number(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0 || n == 1) {
        return 1;
    }

    unsigned long long **bell = (unsigned long long **)malloc((n + 1) * sizeof(unsigned long long *));
    if (bell == NULL) {
        return 0;
    }

    for (int i = 0; i <= n; i++) {
        bell[i] = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
        if (bell[i] == NULL) {
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

int main() {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n < 0 || n > 50) { 
        return 1;
    }

    unsigned long long result = bell_number(n);
    printf("%llu\n", result);

    return 0;
}
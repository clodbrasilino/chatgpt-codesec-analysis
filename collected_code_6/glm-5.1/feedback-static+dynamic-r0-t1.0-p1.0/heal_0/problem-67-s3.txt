#include <stdio.h>
#include <stdlib.h>

unsigned long long bell_number(int n) {
    unsigned long long **bell = malloc((n + 1) * sizeof(unsigned long long *));
    if (bell == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= n; i++) {
        bell[i] = malloc((i + 1) * sizeof(unsigned long long));
        if (bell[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(bell[j]);
            }
            free(bell);
            exit(EXIT_FAILURE);
        }
    }
    bell[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        bell[i][0] = bell[i - 1][i - 1];
        for (int j = 1; j <= i; j++) {
            bell[i][j] = bell[i][j - 1] + bell[i - 1][j - 1];
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
    int n = 10;
    printf("%llu\n", bell_number(n));
    return 0;
}
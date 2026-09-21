#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 10000

int findLongestRepeatingSubseq(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int n = 0;
    while (n < MAX_STR_LEN && str[n] != '\0') {
        n++;
    }

    if (n == 0) {
        return 0;
    }

    int *prev = (int *)calloc(n + 1, sizeof(int));
    int *curr = (int *)calloc(n + 1, sizeof(int));
    
    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                curr[j] = 1 + prev[j - 1];
            } else {
                curr[j] = (curr[j - 1] > prev[j]) ? curr[j - 1] : prev[j];
            }
        }
        for (int j = 0; j <= n; j++) {
            prev[j] = curr[j];
        }
    }

    int res = curr[n];

    free(prev);
    free(curr);

    return res;
}

int main(void) {
    char str[MAX_STR_LEN + 1];
    if (scanf("%10000s", str) == 1) {
        int length = findLongestRepeatingSubseq(str);
        printf("%d\n", length);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int max_value(int a, int b)
{
    return (a > b) ? a : b;
}

int longest_repeating_subsequence(const char *str)
{
    size_t n;
    size_t i;
    size_t j;
    int *prev;
    int *curr;
    int *tmp;
    int result;

    if (str == NULL) {
        return -1;
    }

    n = strlen(str);
    if (n < 2) {
        return 0;
    }

    if (n + 1 > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    prev = calloc(n + 1, sizeof(int));
    if (prev == NULL) {
        return -1;
    }

    curr = calloc(n + 1, sizeof(int));
    if (curr == NULL) {
        free(prev);
        prev = NULL;
        return -1;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                curr[j] = prev[j - 1] + 1;
            } else {
                curr[j] = max_value(prev[j], curr[j - 1]);
            }
        }
        tmp = prev;
        prev = curr;
        curr = tmp;
    }

    result = prev[n];

    free(prev);
    prev = NULL;
    free(curr);
    curr = NULL;

    return result;
}

int main(void)
{
    char str[100001];

    while (scanf("%100000s", str) == 1) {
        int result = longest_repeating_subsequence(str);

        if (result >= 0) {
            printf("%d\n", result);
        }
    }

    return EXIT_SUCCESS;
}
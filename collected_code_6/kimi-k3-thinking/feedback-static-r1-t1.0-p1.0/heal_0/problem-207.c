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
    size_t dim;
    size_t total;
    size_t i;
    size_t j;
    int *dp;
    int result;

    if (str == NULL) {
        return -1;
    }

    n = strlen(str);
    if (n < 2) {
        return 0;
    }

    dim = n + 1;
    if (dim > SIZE_MAX / dim) {
        return -1;
    }

    total = dim * dim;
    if (total > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    dp = calloc(total, sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (str[i - 1] == str[j - 1] && i != j) {
                dp[i * dim + j] = dp[(i - 1) * dim + (j - 1)] + 1;
            } else {
                dp[i * dim + j] = max_value(dp[(i - 1) * dim + j],
                                            dp[i * dim + (j - 1)]);
            }
        }
    }

    result = dp[n * dim + n];
    free(dp);
    dp = NULL;

    return result;
}

int main(void)
{
    const char *test1 = "aabb";
    const char *test2 = "aab";
    const char *test3 = "axxxy";
    int r1;
    int r2;
    int r3;

    r1 = longest_repeating_subsequence(test1);
    r2 = longest_repeating_subsequence(test2);
    r3 = longest_repeating_subsequence(test3);

    if (r1 >= 0) {
        printf("LRS length of \"%s\": %d\n", test1, r1);
    } else {
        fprintf(stderr, "Error computing LRS for \"%s\"\n", test1);
    }

    if (r2 >= 0) {
        printf("LRS length of \"%s\": %d\n", test2, r2);
    } else {
        fprintf(stderr, "Error computing LRS for \"%s\"\n", test2);
    }

    if (r3 >= 0) {
        printf("LRS length of \"%s\": %d\n", test3, r3);
    } else {
        fprintf(stderr, "Error computing LRS for \"%s\"\n", test3);
    }

    return EXIT_SUCCESS;
}
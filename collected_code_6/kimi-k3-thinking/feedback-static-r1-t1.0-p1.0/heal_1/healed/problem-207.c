#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096u

static int max_value(int a, int b)
{
    return (a > b) ? a : b;
}

static size_t safe_strnlen(const char *s, size_t max_len)
{
    size_t len = 0u;

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
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

    n = safe_strnlen(str, MAX_INPUT_LEN);
    if (n == MAX_INPUT_LEN) {
        return -1;
    }

    if (n < 2u) {
        return 0;
    }

    dim = n + 1u;
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

    for (i = 1u; i <= n; i++) {
        for (j = 1u; j <= n; j++) {
            if (str[i - 1u] == str[j - 1u] && i != j) {
                dp[i * dim + j] = dp[(i - 1u) * dim + (j - 1u)] + 1;
            } else {
                dp[i * dim + j] = max_value(dp[(i - 1u) * dim + j],
                                            dp[i * dim + (j - 1u)]);
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
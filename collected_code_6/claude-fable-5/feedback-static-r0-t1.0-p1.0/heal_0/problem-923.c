#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t shortest_supersequence_length(const char *str1, const char *str2);

static size_t shortest_supersequence_length(const char *str1, const char *str2)
{
    size_t m;
    size_t n;
    size_t i;
    size_t j;
    size_t result;
    size_t *prev;
    size_t *curr;
    size_t *tmp;

    if (str1 == NULL || str2 == NULL) {
        return 0U;
    }

    m = strlen(str1);
    n = strlen(str2);

    prev = malloc((n + 1U) * sizeof(size_t));
    if (prev == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    curr = malloc((n + 1U) * sizeof(size_t));
    if (curr == NULL) {
        free(prev);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (j = 0U; j <= n; j++) {
        prev[j] = j;
    }

    for (i = 1U; i <= m; i++) {
        curr[0] = i;
        for (j = 1U; j <= n; j++) {
            if (str1[i - 1U] == str2[j - 1U]) {
                curr[j] = prev[j - 1U] + 1U;
            } else {
                if (prev[j] < curr[j - 1U]) {
                    curr[j] = prev[j] + 1U;
                } else {
                    curr[j] = curr[j - 1U] + 1U;
                }
            }
        }
        tmp = prev;
        prev = curr;
        curr = tmp;
    }

    result = prev[n];

    free(prev);
    free(curr);

    return result;
}

int main(void)
{
    const char *str1 = "geek";
    const char *str2 = "eke";
    size_t length;

    length = shortest_supersequence_length(str1, str2);

    if (printf("Length of the shortest supersequence of \"%s\" and \"%s\" is %zu\n",
               str1, str2, length) < 0) {
        return EXIT_FAILURE;
    }

    str1 = "AGGTAB";
    str2 = "GXTXAYB";
    length = shortest_supersequence_length(str1, str2);

    if (printf("Length of the shortest supersequence of \"%s\" and \"%s\" is %zu\n",
               str1, str2, length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int shortest_common_supersequence_length(
    const char *str1,
    size_t len1,
    const char *str2,
    size_t len2,
    size_t *result)
{
    size_t *previous;
    size_t *current;
    size_t i;
    size_t j;

    if (str1 == NULL || str2 == NULL || result == NULL) {
        return 0;
    }

    if (len1 > SIZE_MAX - len2) {
        return 0;
    }

    if (len2 == SIZE_MAX ||
        len2 + 1U > SIZE_MAX / sizeof(*previous)) {
        return 0;
    }

    previous = calloc(len2 + 1U, sizeof(*previous));
    current = calloc(len2 + 1U, sizeof(*current));

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return 0;
    }

    for (i = 1U; i <= len1; ++i) {
        current[0] = 0U;

        for (j = 1U; j <= len2; ++j) {
            if (str1[i - 1U] == str2[j - 1U]) {
                current[j] = previous[j - 1U] + 1U;
            } else {
                current[j] = previous[j] > current[j - 1U]
                                 ? previous[j]
                                 : current[j - 1U];
            }
        }

        {
            size_t *temporary = previous;
            previous = current;
            current = temporary;
        }
    }

    *result = len1 + len2 - previous[len2];

    free(previous);
    free(current);
    return 1;
}

int main(void)
{
    static const char str1[] = "AGGTAB";
    static const char str2[] = "GXTXAYB";
    size_t length;

    if (!shortest_common_supersequence_length(
            str1,
            sizeof(str1) - 1U,
            str2,
            sizeof(str2) - 1U,
            &length)) {
        fputs("Unable to calculate the length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
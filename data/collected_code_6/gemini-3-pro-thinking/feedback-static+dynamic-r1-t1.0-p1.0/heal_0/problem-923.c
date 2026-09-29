#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_shortest_supersequence_length(const char *str1, const char *str2, size_t *out_length) {
    if (str1 == NULL || str2 == NULL || out_length == NULL) {
        return -1;
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 == 0) {
        *out_length = len2;
        return 0;
    }
    if (len2 == 0) {
        *out_length = len1;
        return 0;
    }

    size_t *prev = (size_t *)calloc(len2 + 1, sizeof(size_t));
    if (prev == NULL) {
        return -1;
    }

    size_t *curr = (size_t *)calloc(len2 + 1, sizeof(size_t));
    if (curr == NULL) {
        free(prev);
        return -1;
    }

    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                curr[j] = prev[j - 1] + 1;
            } else {
                curr[j] = (prev[j] > curr[j - 1]) ? prev[j] : curr[j - 1];
            }
        }
        memcpy(prev, curr, (len2 + 1) * sizeof(size_t));
    }

    *out_length = len1 + len2 - prev[len2];

    free(prev);
    free(curr);

    return 0;
}

int main(void) {
    const char *str1 = "AGGTAB";
    const char *str2 = "GXTXAYB";
    size_t result_length = 0;

    if (get_shortest_supersequence_length(str1, str2, &result_length) == 0) {
        printf("%zu\n", result_length);
    } else {
        fprintf(stderr, "Error computing shortest common supersequence length.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
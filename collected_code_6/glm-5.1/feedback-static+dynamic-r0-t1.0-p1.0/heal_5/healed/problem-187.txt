#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int longest_common_subsequence(const char *X, const char *Y, size_t x_len, size_t y_len) {
    if (x_len == 0 || y_len == 0) {
        return 0;
    }

    size_t *prev = (size_t *)calloc(y_len + 1, sizeof(size_t));
    size_t *curr = (size_t *)calloc(y_len + 1, sizeof(size_t));

    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        return -1;
    }

    for (size_t i = 1; i <= x_len; i++) {
        for (size_t j = 1; j <= y_len; j++) {
            if (X[i - 1] == Y[j - 1]) {
                curr[j] = prev[j - 1] + 1;
            } else {
                curr[j] = (prev[j] > curr[j - 1]) ? prev[j] : curr[j - 1];
            }
        }
        size_t *temp = prev;
        prev = curr;
        curr = temp;
        memset(curr, 0, (y_len + 1) * sizeof(size_t));
    }

    size_t result = prev[y_len];
    free(prev);
    free(curr);

    return (result > INT_MAX) ? -1 : (int)result;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Invalid input strings.\n");
        return EXIT_FAILURE;
    }

    size_t m = strlen(argv[1]);
    size_t n = strlen(argv[2]);

    int result = longest_common_subsequence(argv[1], argv[2], m, n);
    if (result < 0) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}
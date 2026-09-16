#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longest_common_subsequence(const char *X, const char *Y) {
    size_t m = strlen(X);
    size_t n = strlen(Y);

    if (m == 0 || n == 0) {
        return 0;
    }

    size_t *prev = (size_t *)calloc(n + 1, sizeof(size_t));
    size_t *curr = (size_t *)calloc(n + 1, sizeof(size_t));

    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        return -1;
    }

    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                curr[j] = prev[j - 1] + 1;
            } else {
                curr[j] = (prev[j] > curr[j - 1]) ? prev[j] : curr[j - 1];
            }
        }
        size_t *temp = prev;
        prev = curr;
        curr = temp;
        memset(curr, 0, (n + 1) * sizeof(size_t));
    }

    size_t result = prev[n];
    free(prev);
    free(curr);

    return (int)result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Invalid input strings.\n");
        return EXIT_FAILURE;
    }

    int result = longest_common_subsequence(argv[1], argv[2]);
    if (result < 0) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}
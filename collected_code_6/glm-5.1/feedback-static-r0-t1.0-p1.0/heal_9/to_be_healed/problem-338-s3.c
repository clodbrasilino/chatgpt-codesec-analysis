#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_substrings(const char *str, size_t len) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;

    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t max_len = 1024;
    size_t len = strnlen(argv[1], max_len);

    if (len == max_len) {
        return EXIT_FAILURE;
    }

    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, argv[1], len + 1);

    int result = count_substrings(buffer, len);
    printf("%d\n", result);

    free(buffer);

    return EXIT_SUCCESS;
}
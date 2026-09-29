#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *swap_whitespace_underscore(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strnlen(input, SIZE_MAX);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; ++i) {
        if (input[i] == ' ') {
            result[i] = '_';
        } else if (input[i] == '_') {
            result[i] = ' ';
        } else {
            result[i] = input[i];
        }
    }

    result[len] = '\0';

    return result;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char const * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *processed = swap_whitespace_underscore(argv[1]);
    if (processed == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", processed);
    free(processed);

    return EXIT_SUCCESS;
}
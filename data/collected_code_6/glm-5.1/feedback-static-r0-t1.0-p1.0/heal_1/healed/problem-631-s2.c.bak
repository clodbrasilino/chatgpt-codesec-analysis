#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *swap_whitespace_underscore(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t src_idx = 0;
    size_t dst_idx = 0;

    while (src_idx < len) {
        char current = input[src_idx];
        if (current == ' ') {
            result[dst_idx++] = '_';
        } else if (current == '_') {
            result[dst_idx++] = ' ';
        } else {
            result[dst_idx++] = current;
        }
        src_idx++;
    }

    result[dst_idx] = '\0';

    return result;
}

int main(int argc, char * const argv[]) {
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
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

    size_t src_idx = 0;
    size_t dst_idx = 0;

    while (src_idx < len) {
        char current = input[src_idx];
        if (current == ' ') {
            result[dst_idx++] = '_';
            src_idx++;
        } else if (current == '_') {
            result[dst_idx++] = ' ';
            src_idx++;
        } else {
            size_t chunk_len = 1;
            while (src_idx + chunk_len < len && input[src_idx + chunk_len] != ' ' && input[src_idx + chunk_len] != '_') {
                chunk_len++;
            }
            if (dst_idx + chunk_len <= len) {
                memcpy(result + dst_idx, input + src_idx, chunk_len);
            }
            dst_idx += chunk_len;
            src_idx += chunk_len;
        }
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
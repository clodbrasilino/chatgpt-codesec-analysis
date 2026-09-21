#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *remove_non_alnum(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (len < SIZE_MAX && str[len] != '\0') {
        len++;
    }

    size_t result_capacity = len + 1;
    char *result = malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }

    size_t dest_idx = 0;
    const char *current_ptr = str;

    while (*current_ptr != '\0') {
        if ((*current_ptr >= 'a' && *current_ptr <= 'z') ||
            (*current_ptr >= 'A' && *current_ptr <= 'Z') ||
            (*current_ptr >= '0' && *current_ptr <= '9')) {
            
            if (dest_idx < result_capacity - 1) {
                result[dest_idx++] = *current_ptr;
            }
        }
        current_ptr++;
    }

    result[dest_idx] = '\0';

    char *shrunk_result = realloc(result, dest_idx + 1);
    if (shrunk_result != NULL) {
        result = shrunk_result;
    }

    return result;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *filtered = remove_non_alnum(argv[1]);
    if (filtered == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    printf("%s\n", filtered);
    free(filtered);

    return 0;
}
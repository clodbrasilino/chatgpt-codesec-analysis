#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuples(const char *tuple[], size_t n, const char *delimiter) {
    if (n == 0) return NULL;

    size_t delimiter_len = (delimiter != NULL) ? strlen(delimiter) : 0;
    size_t total_len = 1; // Null terminator
    for (size_t i = 0; i < n; ++i) {
        if (tuple[i] != NULL) {
            total_len += strlen(tuple[i]);
        }
    }
    total_len += (n - 1) * delimiter_len;

    char *result = (char *)malloc(total_len);
    if (result == NULL) return NULL;

    result[0] = '\0';
    size_t current_pos = 0;
    for (size_t i = 0; i < n; ++i) {
        if (tuple[i] != NULL) {
            size_t len = strlen(tuple[i]);
            memcpy(result + current_pos, tuple[i], len);
            current_pos += len;
        }
        if (i < n - 1 && delimiter != NULL) {
            size_t len = strlen(delimiter);
            memcpy(result + current_pos, delimiter, len);
            current_pos += len;
        }
    }
    result[total_len - 1] = '\0';

    return result;
}

int main() {
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t n = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ",";

    char *result = concat_tuples(tuple, n, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}
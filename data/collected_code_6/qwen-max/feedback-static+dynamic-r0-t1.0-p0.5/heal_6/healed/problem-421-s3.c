#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuples(const char *tuple[], size_t len, const char *delimiter) {
    if (len == 0) return NULL;

    size_t delimiter_len = (delimiter != NULL && *delimiter != '\0') ? strnlen(delimiter, 1024) : 0;
    size_t total_len = 0;
    for (size_t i = 0; i < len; ++i) {
        const char *str = tuple[i];
        if (str != NULL) {
            total_len += strnlen(str, 1024);
        }
    }
    total_len += (len - 1) * delimiter_len + 1;

    char *result = (char *)malloc(total_len);
    if (result == NULL) return NULL;

    result[0] = '\0';
    char *current_pos = result;
    for (size_t i = 0; i < len; ++i) {
        const char *str = tuple[i];
        if (str != NULL) {
            size_t str_len = strnlen(str, 1024);
            memcpy(current_pos, str, str_len);
            current_pos += str_len;
        }
        if (i < len - 1 && delimiter != NULL && *delimiter != '\0') {
            size_t delim_len = strnlen(delimiter, 1024);
            memcpy(current_pos, delimiter, delim_len);
            current_pos += delim_len;
        }
    }
    *current_pos = '\0';

    return result;
}

int main() {
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ",";

    char *result = concat_tuples(tuple, len, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}
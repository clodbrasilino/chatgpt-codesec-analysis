#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuples(const char **tuple, size_t tuple_size, const char *delimiter) {
    if (tuple_size == 0) return NULL;

    size_t delimiter_len = 0;
    if (delimiter) {
        delimiter_len = strnlen(delimiter, 1024);
    }
    size_t total_length = 0;
    for (size_t i = 0; i < tuple_size; ++i) {
        total_length += strnlen(tuple[i], 1024);
    }
    total_length += (tuple_size - 1) * delimiter_len + 1;

    char *result = (char *)malloc(total_length);
    if (!result) return NULL;

    result[0] = '\0';
    for (size_t i = 0; i < tuple_size; ++i) {
        size_t tuple_len = strnlen(tuple[i], 1024);
        if (tuple_len + strlen(result) < total_length) {
            strncat(result, tuple[i], tuple_len);
        }
        if (i < tuple_size - 1 && delimiter) {
            size_t new_len = strlen(result) + delimiter_len;
            if (new_len <= total_length) {
                strncat(result, delimiter, delimiter_len);
            }
        }
    }

    return result;
}

int main() {
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ",";

    char *result = concat_tuples(tuple, tuple_size, delimiter);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Failed to concatenate strings\n");
    }

    return 0;
}
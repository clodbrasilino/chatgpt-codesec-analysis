#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_with_delimiter(const char *delimiter, const char **tuple, size_t tuple_size) {
    if (tuple_size == 0) return NULL;

    size_t delimiter_len = strlen(delimiter);
    size_t total_len = 0;
    for (size_t i = 0; i < tuple_size; ++i) {
        total_len += strlen(tuple[i]);
    }
    total_len += delimiter_len * (tuple_size - 1);

    char *result = (char *)malloc(total_len + 1);
    if (result == NULL) return NULL;

    result[0] = '\0';
    for (size_t i = 0; i < tuple_size; ++i) {
        strcat(result, tuple[i]);
        if (i < tuple_size - 1) {
            strcat(result, delimiter);
        }
    }

    return result;
}

int main() {
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ",";

    char *result = concat_with_delimiter(delimiter, tuple, tuple_size);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}
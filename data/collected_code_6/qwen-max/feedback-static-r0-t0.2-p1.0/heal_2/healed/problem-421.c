#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuples(const char *tuple[], size_t len, const char *delimiter) {
    if (len == 0) return NULL;

    size_t delimiter_len = strnlen(delimiter, 64);
    size_t total_len = 0;
    for (size_t i = 0; i < len; ++i) {
        total_len += strnlen(tuple[i], 256);
    }
    total_len += (len - 1) * delimiter_len + 1;

    char *result = (char *)malloc(total_len);
    if (result == NULL) return NULL;

    result[0] = '\0';
    for (size_t i = 0, pos = 0; i < len; ++i) {
        pos += snprintf(result + pos, total_len - pos, "%s", tuple[i]);
        if (i < len - 1) {
            pos += snprintf(result + pos, total_len - pos, "%s", delimiter);
        }
    }

    return result;
}

int main() {
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ",";

    char *result = concatenate_tuples(tuple, len, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuples(const char *tuple[], size_t len, const char *delimiter) {
    if (len == 0) return NULL;

    size_t delimiter_len = (delimiter ? strnlen(delimiter, 1024) : 0);
    size_t total_len = 0;

    for (size_t i = 0; i < len; ++i) {
        const char *item = tuple[i];
        if (item != NULL) {
            total_len += strnlen(item, 1024);
        }
    }
    total_len += (len - 1) * delimiter_len + 1;

    char *result = (char *)malloc(total_len);
    if (result == NULL) return NULL;

    result[0] = '\0';
    char *pos = result;

    for (size_t i = 0; i < len; ++i) {
        const char *item = tuple[i];
        if (item != NULL) {
            size_t item_len = strnlen(item, 1024);
            if (item_len > 0) {
                memcpy(pos, item, item_len);
                pos += item_len;
                if (i < len - 1 && delimiter_len > 0) {
                    memcpy(pos, delimiter, delimiter_len);
                    pos += delimiter_len;
                }
            }
        }
    }

    *pos = '\0';
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
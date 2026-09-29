#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_with_delimiter(const char *tuple[], size_t tuple_size, const char *delimiter) {
    if (tuple_size == 0) return NULL;

    size_t delimiter_len = strlen(delimiter);
    size_t total_len = 0;
    for (size_t i = 0; i < tuple_size; ++i) {
        total_len += strlen(tuple[i]);
    }
    total_len += (tuple_size - 1) * delimiter_len + 1;

    char *result = (char *)malloc(total_len * sizeof(char));
    if (result == NULL) return NULL;

    size_t pos = 0;
    for (size_t i = 0; i < tuple_size; ++i) {
        size_t len = strlen(tuple[i]);
        memcpy(result + pos, tuple[i], len);
        pos += len;
        if (i < tuple_size - 1) {
            memcpy(result + pos, delimiter, delimiter_len);
            pos += delimiter_len;
        }
    }
    result[total_len - 1] = '\0';

    return result;
}

int main() {
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t tuple_size = 3;
    const char *delimiter = ",";

    char *result = concat_with_delimiter(tuple, tuple_size, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}
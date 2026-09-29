#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *concat_with_delimiter(const char *delimiter, const char **tuple, size_t tuple_size) {
    if (tuple_size == 0) return NULL;

    size_t delimiter_len = safe_strlen(delimiter, SIZE_MAX);
    size_t total_len = 0;
    for (size_t i = 0; i < tuple_size; ++i) {
        total_len += safe_strlen(tuple[i], SIZE_MAX);
    }
    total_len += delimiter_len * (tuple_size - 1);

    char *result = (char *)malloc(total_len + 1);
    if (result == NULL) return NULL;

    result[0] = '\0';
    size_t pos = 0;
    for (size_t i = 0; i < tuple_size; ++i) {
        size_t len = safe_strlen(tuple[i], SIZE_MAX);
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(result + pos, tuple[i], len);
        pos += len;
        if (i < tuple_size - 1) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result + pos, delimiter, delimiter_len);
            pos += delimiter_len;
        }
    }
    result[total_len] = '\0';

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
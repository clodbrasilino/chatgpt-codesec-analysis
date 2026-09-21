#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuples(const char **tuple, int size, const char *delimiter) {
    if (size <= 0 || !tuple || !*tuple || !delimiter) return NULL;

    size_t delimiter_len = strlen(delimiter);
    size_t total_len = 0;
    for (int i = 0; i < size; ++i) {
        size_t len = strlen(tuple[i]);
        if (len == 0) return NULL;
        total_len += len;
    }
    total_len += (size - 1) * delimiter_len + 1;

    char *result = malloc(total_len * sizeof(char));
    if (!result) return NULL;

    char *p = result;
    for (int i = 0; i < size; ++i) {
        size_t len = snprintf(p, total_len, "%s", tuple[i]);
        p += len;
        total_len -= len;
        if (i < size - 1) {
            len = snprintf(p, total_len, "%s", delimiter);
            p += len;
            total_len -= len;
        }
    }

    return result;
}

int main() {
    const char *tuple[] = {"Hello", "World", "C", "Programming"};
    int size = 4;
    const char *delimiter = "-";

    char *result = concat_tuples(tuple, size, delimiter);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *tuple_join(const char **tuple, size_t count, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(size_t)) {
        return NULL;
    }

    size_t *lengths = (size_t *)malloc(count * sizeof(size_t));
    if (lengths == NULL) {
        return NULL;
    }

    size_t delim_len = strlen(delimiter);
    size_t total_len = 0;

    for (size_t i = 0; i < count; i++) {
        if (tuple[i] == NULL) {
            free(lengths);
            return NULL;
        }
        lengths[i] = strlen(tuple[i]);
        if (lengths[i] > SIZE_MAX - total_len) {
            free(lengths);
            return NULL;
        }
        total_len += lengths[i];
        if (i < count - 1) {
            if (delim_len > SIZE_MAX - total_len) {
                free(lengths);
                return NULL;
            }
            total_len += delim_len;
        }
    }

    if (total_len == SIZE_MAX) {
        free(lengths);
        return NULL;
    }

    size_t result_size = total_len + 1;
    char *result = (char *)malloc(result_size);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    size_t written = 0;
    for (size_t i = 0; i < count; i++) {
        if (written + lengths[i] > total_len) {
            free(lengths);
            free(result);
            return NULL;
        }
        memcpy(result + written, tuple[i], lengths[i]);
        written += lengths[i];
        
        if (i < count - 1) {
            if (written + delim_len > total_len) {
                free(lengths);
                free(result);
                return NULL;
            }
            memcpy(result + written, delimiter, delim_len);
            written += delim_len;
        }
    }

    result[written] = '\0';
    free(lengths);

    return result;
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry", "date"};
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ", ";

    char *result = tuple_join(tuple, count, delimiter);
    if (result == NULL) {
        fprintf(stderr, "Failed to join tuple\n");
        return 1;
    }

    printf("%s\n", result);

    free(result);

    return 0;
}
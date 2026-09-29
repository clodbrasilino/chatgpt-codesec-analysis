#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *tuple_join(const char **tuple, size_t count, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    size_t delim_len = strnlen(delimiter, SIZE_MAX);
    if (delim_len == SIZE_MAX) {
        return NULL;
    }

    size_t total_len = 0;

    for (size_t i = 0; i < count; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        
        size_t max_len = SIZE_MAX - total_len;
        size_t len = strnlen(tuple[i], max_len);
        if (len == max_len) {
            return NULL;
        }
        total_len += len;
        
        if (i < count - 1) {
            if (delim_len > SIZE_MAX - total_len) {
                return NULL;
            }
            total_len += delim_len;
        }
    }

    if (total_len == SIZE_MAX) {
        return NULL;
    }

    size_t result_size = total_len + 1;
    char *result = malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    size_t written = 0;
    for (size_t i = 0; i < count; i++) {
        size_t remaining = result_size - written;
        int n = snprintf(result + written, remaining, "%s", tuple[i]);
        if (n < 0 || (size_t)n >= remaining) {
            free(result);
            return NULL;
        }
        written += n;
        
        if (i < count - 1) {
            remaining = result_size - written;
            n = snprintf(result + written, remaining, "%s", delimiter);
            if (n < 0 || (size_t)n >= remaining) {
                free(result);
                return NULL;
            }
            written += n;
        }
    }

    result[written] = '\0';

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
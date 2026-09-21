#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *concat_tuple(const char **tuple, size_t size, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL) {
        return NULL;
    }

    size_t delim_length = safe_strlen(delimiter, SIZE_MAX);
    size_t total_length = 0;
    size_t *lengths = NULL;

    if (size > 0) {
        lengths = (size_t *)malloc(size * sizeof(size_t));
        if (lengths == NULL) {
            return NULL;
        }
    }

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            free(lengths);
            return NULL;
        }
        lengths[i] = safe_strlen(tuple[i], SIZE_MAX - total_length);
        if (total_length > SIZE_MAX - lengths[i]) {
            free(lengths);
            return NULL;
        }
        total_length += lengths[i];
        if (i < size - 1) {
            if (total_length > SIZE_MAX - delim_length) {
                free(lengths);
                return NULL;
            }
            total_length += delim_length;
        }
    }

    if (total_length >= SIZE_MAX) {
        free(lengths);
        return NULL;
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    char *current = result;
    for (size_t i = 0; i < size; i++) {
        size_t remaining = total_length - (size_t)(current - result);
        if (lengths[i] > remaining) {
            free(result);
            free(lengths);
            return NULL;
        }
        if (lengths[i] > 0) {
            if (current + lengths[i] > result + total_length) {
                free(result);
                free(lengths);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(current, tuple[i], lengths[i]);
        }
        current += lengths[i];
        if (i < size - 1) {
            remaining = total_length - (size_t)(current - result);
            if (delim_length > remaining) {
                free(result);
                free(lengths);
                return NULL;
            }
            if (delim_length > 0) {
                if (current + delim_length > result + total_length) {
                    free(result);
                    free(lengths);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(current, delimiter, delim_length);
            }
            current += delim_length;
        }
    }
    *current = '\0';

    free(lengths);
    return result;
}

int main(void) {
    const char *tuple1[] = {"Hello", "World", "C"};
    const char *tuple2[] = {"apple", "banana", "cherry", "date"};
    const char *tuple3[] = {"single"};
    const char *tuple4[] = {"", "empty", ""};

    char *result1 = concat_tuple(tuple1, 3, "-");
    char *result2 = concat_tuple(tuple2, 4, ", ");
    char *result3 = concat_tuple(tuple3, 1, "|");
    char *result4 = concat_tuple(tuple4, 3, "::");

    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    if (result4 != NULL) {
        printf("%s\n", result4);
        free(result4);
    }

    return 0;
}
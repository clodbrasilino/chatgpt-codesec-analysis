#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

#define MAX_STRING_LEN 65535

char **adjacent_concatenate(const char *const *tuple, size_t len) {
    if (tuple == NULL || len < 2) {
        return NULL;
    }

    if (len - 1 > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    char **result = malloc((len - 1) * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len - 1; ++i) {
        if (tuple[i] == NULL || tuple[i + 1] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        size_t left_len = 0;
        while (left_len <= MAX_STRING_LEN && tuple[i][left_len] != '\0') {
            left_len++;
        }
        if (left_len > MAX_STRING_LEN) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        size_t right_len = 0;
        while (right_len <= MAX_STRING_LEN && tuple[i + 1][right_len] != '\0') {
            right_len++;
        }
        if (right_len > MAX_STRING_LEN) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        if (left_len > SIZE_MAX - right_len - 1) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        size_t total = left_len + right_len + 1;
        result[i] = malloc(total);
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        int written = snprintf(result[i], total, "%s%s", tuple[i], tuple[i + 1]);
        if (written < 0 || (size_t)written >= total) {
            free(result[i]);
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
    }

    return result;
}

int main(void) {
    const char *tuple[] = {"one", "two", "three", "four"};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);

    char **result = adjacent_concatenate(tuple, len);
    if (result == NULL) {
        fprintf(stderr, "Unable to concatenate adjacent elements\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < len - 1; ++i) {
        puts(result[i]);
        free(result[i]);
    }
    free(result);

    return EXIT_SUCCESS;
}
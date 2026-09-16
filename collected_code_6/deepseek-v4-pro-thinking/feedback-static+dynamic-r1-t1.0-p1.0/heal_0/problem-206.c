#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **adjacent_concatenate(const char *const *tuple, size_t len) {
    if (tuple == NULL || len < 2) {
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

        size_t left_len = strlen(tuple[i]);
        size_t right_len = strlen(tuple[i + 1]);

        result[i] = malloc(left_len + right_len + 1);
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        memcpy(result[i], tuple[i], left_len);
        memcpy(result[i] + left_len, tuple[i + 1], right_len + 1);
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
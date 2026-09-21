#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

static size_t get_bounded_len(const char *str, size_t max_len) {
    const char *end = memchr(str, '\0', max_len);
    return end ? (size_t)(end - str) : max_len;
}

char **concatenate_adjacent(const char *const *tuple, size_t size, size_t *out_size) {
    if (!tuple || !out_size) {
        return NULL;
    }

    if (size < 2) {
        *out_size = 0;
        return NULL;
    }

    *out_size = size - 1;
    char **result = malloc((*out_size) * sizeof(char *));
    if (!result) {
        return NULL;
    }

    for (size_t i = 0; i < *out_size; ++i) {
        if (!tuple[i] || !tuple[i + 1]) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        size_t len1 = get_bounded_len(tuple[i], MAX_STRING_LEN);
        size_t len2 = get_bounded_len(tuple[i + 1], MAX_STRING_LEN);
        
        size_t total_len = len1 + len2 + 1;
        result[i] = malloc(total_len);
        if (!result[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        snprintf(result[i], total_len, "%.*s%.*s", (int)len1, tuple[i], (int)len2, tuple[i + 1]);
    }

    return result;
}

int main(void) {
    const char *input_tuple[] = {"Apple", "Banana", "Cherry", "Date"};
    size_t input_size = sizeof(input_tuple) / sizeof(input_tuple[0]);
    size_t out_size = 0;

    char **concatenated = concatenate_adjacent(input_tuple, input_size, &out_size);

    if (concatenated) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%s\n", concatenated[i]);
            free(concatenated[i]);
        }
        free(concatenated);
    }

    return 0;
}
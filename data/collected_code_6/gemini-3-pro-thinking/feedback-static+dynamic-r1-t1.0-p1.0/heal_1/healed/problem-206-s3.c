#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

char **concatenate_adjacent(const char *const *tuples, size_t count, size_t *out_count) {
    if (!tuples || !out_count) {
        if (out_count) {
            *out_count = 0;
        }
        return NULL;
    }

    if (count < 2) {
        *out_count = 0;
        return NULL;
    }

    size_t new_count = count - 1;
    char **result = malloc(new_count * sizeof(char *));
    if (!result) {
        *out_count = 0;
        return NULL;
    }

    for (size_t i = 0; i < new_count; i++) {
        if (!tuples[i] || !tuples[i + 1]) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *out_count = 0;
            return NULL;
        }

        size_t len1 = strnlen(tuples[i], MAX_STR_LEN);
        size_t len2 = strnlen(tuples[i + 1], MAX_STR_LEN);
        
        size_t req_size = len1 + len2 + 1;
        result[i] = malloc(req_size);
        if (!result[i]) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *out_count = 0;
            return NULL;
        }
        
        snprintf(result[i], req_size, "%.*s%.*s", (int)len1, tuples[i], (int)len2, tuples[i + 1]);
    }

    *out_count = new_count;
    return result;
}

int main(void) {
    const char *const tuples[] = {"alpha", "beta", "gamma", "delta", "epsilon"};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t out_count = 0;

    char **result = concatenate_adjacent(tuples, count, &out_count);

    if (result) {
        for (size_t i = 0; i < out_count; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}
#define _POSIX_C_SOURCE 200809L
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_at_uppercase(const char *str, size_t *count) {
    if (count == NULL) return NULL;
    *count = 0;
    if (str == NULL) return NULL;

    size_t capacity = 16;
    size_t *starts = malloc(capacity * sizeof(size_t));
    if (starts == NULL) return NULL;

    starts[0] = 0;
    size_t nstarts = 1;

    const char *p = str;
    size_t idx = 0;
    while (*p != '\0') {
        if (idx > 0 && isupper((unsigned char)*p)) {
            if (nstarts >= capacity) {
                size_t max_cap = ((size_t)-1 / sizeof(size_t)) / 2;
                if (capacity >= max_cap) {
                    free(starts);
                    return NULL;
                }
                capacity *= 2;
                size_t *tmp = realloc(starts, capacity * sizeof(size_t));
                if (tmp == NULL) {
                    free(starts);
                    return NULL;
                }
                starts = tmp;
            }
            starts[nstarts++] = idx;
        }
        idx++;
        p++;
    }

    size_t len = idx;

    char **result = malloc((nstarts + 1) * sizeof(char *));
    if (result == NULL) {
        free(starts);
        return NULL;
    }

    for (size_t i = 0; i < nstarts; i++) {
        size_t start = starts[i];
        size_t end = (i + 1 < nstarts) ? starts[i + 1] : len;
        size_t seg_len = end - start;

        result[i] = malloc(seg_len + 1);
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            free(starts);
            return NULL;
        }

        for (size_t k = 0; k < seg_len; k++) {
            result[i][k] = str[start + k];
        }
        result[i][seg_len] = '\0';
    }

    result[nstarts] = NULL;
    free(starts);
    *count = nstarts;
    return result;
}

int main(void) {
    const char *input = "HelloWorldHowAreYou";
    size_t count = 0;
    char **parts = split_at_uppercase(input, &count);

    if (parts == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", parts[i]);
        free(parts[i]);
    }
    free(parts);
    return EXIT_SUCCESS;
}
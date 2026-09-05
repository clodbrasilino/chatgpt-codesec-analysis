#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_lowercase(const char *str, size_t *count) {
    size_t capacity = 16;
    size_t idx = 0;

    char **result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    const char *start = str;
    const char *p = str;

    while (*p) {
        if (islower((unsigned char)*p)) {
            size_t seg_len = p - start;
            if (seg_len > 0) {
                if (idx >= capacity) {
                    capacity *= 2;
                    char **tmp = realloc(result, capacity * sizeof(char *));
                    if (tmp == NULL) {
                        for (size_t i = 0; i < idx; i++) {
                            free(result[i]);
                        }
                        free(result);
                        return NULL;
                    }
                    result = tmp;
                }
                result[idx] = malloc(seg_len + 1);
                if (result[idx] == NULL) {
                    for (size_t i = 0; i < idx; i++) {
                        free(result[i]);
                    }
                    free(result);
                    return NULL;
                }
                memcpy(result[idx], start, seg_len);
                result[idx][seg_len] = '\0';
                idx++;
            }
            start = p + 1;
        }
        p++;
    }

    size_t seg_len = p - start;
    if (seg_len > 0) {
        if (idx >= capacity) {
            capacity++;
            char **tmp = realloc(result, capacity * sizeof(char *));
            if (tmp == NULL) {
                for (size_t i = 0; i < idx; i++) {
                    free(result[i]);
                }
                free(result);
                return NULL;
            }
            result = tmp;
        }
        result[idx] = malloc(seg_len + 1);
        if (result[idx] == NULL) {
            for (size_t i = 0; i < idx; i++) {
                free(result[i]);
            }
            free(result);
            return NULL;
        }
        memcpy(result[idx], start, seg_len);
        result[idx][seg_len] = '\0';
        idx++;
    }

    char **final_result = realloc(result, (idx + 1) * sizeof(char *));
    if (final_result == NULL) {
        for (size_t i = 0; i < idx; i++) {
            free(result[i]);
        }
        free(result);
        return NULL;
    }
    result = final_result;
    result[idx] = NULL;

    *count = idx;
    return result;
}

int main(void) {
    const char *input = "ABCdEFGhIJKlMNO";
    size_t count = 0;

    char **parts = split_at_lowercase(input, &count);
    if (parts == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", parts[i]);
        free(parts[i]);
    }
    free(parts);

    return 0;
}
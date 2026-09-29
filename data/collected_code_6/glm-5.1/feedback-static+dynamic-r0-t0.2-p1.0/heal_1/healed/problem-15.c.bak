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
    for (const char *p = str; ; p++) {
        if (*p == '\0' || islower((unsigned char)*p)) {
            size_t seg_len = p - start;
            char *segment = malloc(seg_len + 1);
            if (segment == NULL) {
                for (size_t i = 0; i < idx; i++) {
                    free(result[i]);
                }
                free(result);
                return NULL;
            }
            memcpy(segment, start, seg_len);
            segment[seg_len] = '\0';

            if (idx == capacity) {
                capacity *= 2;
                char **new_result = realloc(result, capacity * sizeof(char *));
                if (new_result == NULL) {
                    free(segment);
                    for (size_t i = 0; i < idx; i++) {
                        free(result[i]);
                    }
                    free(result);
                    return NULL;
                }
                result = new_result;
            }

            result[idx++] = segment;
            start = p + 1;
        }

        if (*p == '\0') {
            break;
        }
    }

    *count = idx;
    return result;
}

int main(void) {
    const char *input = "ABCdefGHIjklMNO";
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
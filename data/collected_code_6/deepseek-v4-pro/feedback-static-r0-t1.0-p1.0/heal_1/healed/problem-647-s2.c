#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_uppercase(const char *str, int *count) {
    if (!str || !count) {
        return NULL;
    }

    size_t len = strnlen(str, 65536);
    size_t max_parts = len + 1;
    char **parts = malloc(max_parts * sizeof(char *));
    if (!parts) {
        return NULL;
    }

    int part_count = 0;
    size_t start = 0;

    for (size_t i = 0; i <= len; i++) {
        if (i == len || (i > 0 && isupper((unsigned char)str[i]))) {
            size_t part_len = i - start;
            if (part_len > 0) {
                size_t alloc_size = part_len + 1;
                if (alloc_size < part_len) {
                    for (int j = 0; j < part_count; j++) {
                        free(parts[j]);
                    }
                    free(parts);
                    return NULL;
                }
                parts[part_count] = malloc(alloc_size * sizeof(char));
                if (!parts[part_count]) {
                    for (int j = 0; j < part_count; j++) {
                        free(parts[j]);
                    }
                    free(parts);
                    return NULL;
                }
                if (part_len > 0) {
                    memcpy(parts[part_count], str + start, part_len);
                }
                parts[part_count][part_len] = '\0';
                part_count++;
            }
            start = i;
        }
    }

    if (part_count == 0) {
        free(parts);
        *count = 0;
        return NULL;
    }

    char **result = realloc(parts, part_count * sizeof(char *));
    if (!result) {
        for (int j = 0; j < part_count; j++) {
            free(parts[j]);
        }
        free(parts);
        return NULL;
    }

    *count = part_count;
    return result;
}

int main(void) {
    const char *input = "helloWorldExample";
    int count = 0;

    char **result = split_at_uppercase(input, &count);
    if (!result) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return EXIT_SUCCESS;
}
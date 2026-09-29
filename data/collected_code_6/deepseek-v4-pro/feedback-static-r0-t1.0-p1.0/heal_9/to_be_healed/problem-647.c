#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char **split_at_uppercase(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    if (str[0] == '\0') {
        char **result = malloc(sizeof(char *));
        if (result == NULL) {
            return NULL;
        }
        result[0] = NULL;
        return result;
    }

    size_t str_len = 0;
    while (str[str_len] != '\0') {
        if (str_len == SIZE_MAX) {
            return NULL;
        }
        str_len++;
    }

    if (str_len > SIZE_MAX / 2) {
        return NULL;
    }

    int max_parts = 1;
    for (size_t i = 0; i < str_len; i++) {
        if (isupper((unsigned char)str[i])) {
            max_parts++;
        }
    }

    char **parts = malloc((max_parts + 1) * sizeof(char *));
    if (parts == NULL) {
        return NULL;
    }

    int part_index = 0;
    const char *start = str;
    size_t current_pos = 1;

    while (current_pos <= str_len) {
        if (current_pos == str_len || isupper((unsigned char)str[current_pos])) {
            size_t part_len = (size_t)(&str[current_pos] - start);
            if (part_len > 0) {
                if (part_len > SIZE_MAX - 1) {
                    for (int j = 0; j < part_index; j++) {
                        free(parts[j]);
                    }
                    free(parts);
                    return NULL;
                }
                char *part = malloc(part_len + 1);
                if (part == NULL) {
                    for (int j = 0; j < part_index; j++) {
                        free(parts[j]);
                    }
                    free(parts);
                    return NULL;
                }
                if (part_len > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(part, start, part_len);
                }
                part[part_len] = '\0';
                parts[part_index++] = part;
            }
            start = &str[current_pos];
            if (current_pos == str_len) {
                break;
            }
        }
        current_pos++;
    }

    parts[part_index] = NULL;
    *count = part_index;
    return parts;
}

int main(void) {
    const char *test_str = "helloWorldExampleTest";
    int count = 0;
    char **result = split_at_uppercase(test_str, &count);

    if (result == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }

    if (count == 0) {
        printf("No parts found\n");
        free(result);
        return 0;
    }

    for (int i = 0; i < count; i++) {
        if (result[i] != NULL) {
            printf("%s\n", result[i]);
        }
    }

    for (int i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}
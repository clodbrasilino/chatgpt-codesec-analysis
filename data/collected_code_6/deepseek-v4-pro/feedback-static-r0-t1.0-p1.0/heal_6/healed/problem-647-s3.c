#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

char **split_at_uppercase(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, 4096);
    size_t max_parts = len + 1;
    char **result = malloc(max_parts * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    *count = 0;
    size_t start = 0;
    size_t i;

    for (i = 1; i <= len; i++) {
        if (i == len || isupper((unsigned char)str[i])) {
            size_t part_len = i - start;
            char *part = malloc((part_len + 1) * sizeof(char));
            if (part == NULL) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            if (part_len > 0) {
                if (start + part_len > len) {
                    part_len = len - start;
                }
                memcpy(part, str + start, part_len);
            }
            part[part_len] = '\0';
            result[*count] = part;
            (*count)++;
            start = i;
        }
    }

    return result;
}

int main(void) {
    const char *test = "helloWorldExample";
    int count = 0;
    char **parts = split_at_uppercase(test, &count);

    if (parts == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", parts[i]);
        free(parts[i]);
    }
    free(parts);

    return 0;
}
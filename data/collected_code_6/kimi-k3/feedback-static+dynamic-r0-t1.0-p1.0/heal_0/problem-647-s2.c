#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_uppercase(const char *str, size_t *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        *count = 0;
        return NULL;
    }

    size_t max_parts = 1;
    for (size_t i = 1; i < len; i++) {
        if (isupper((unsigned char)str[i])) {
            max_parts++;
        }
    }

    char **result = malloc(max_parts * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t part_count = 0;
    size_t start = 0;

    for (size_t i = 1; i <= len; i++) {
        if (i == len || isupper((unsigned char)str[i])) {
            size_t part_len = i - start;
            result[part_count] = malloc(part_len + 1);
            if (result[part_count] == NULL) {
                for (size_t j = 0; j < part_count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strncpy(result[part_count], str + start, part_len);
            result[part_count][part_len] = '\0';
            part_count++;
            start = i;
        }
    }

    *count = part_count;
    return result;
}

void free_split_result(char **result, size_t count) {
    if (result == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *test_string = "HelloWorldThisIsATest";
    size_t count = 0;

    char **parts = split_at_uppercase(test_string, &count);

    if (parts == NULL && count == 0) {
        printf("Empty string or error occurred.\n");
        return 1;
    }

    if (parts == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("Split \"%s\" at uppercase letters:\n", test_string);
    for (size_t i = 0; i < count; i++) {
        printf("Part %zu: \"%s\"\n", i + 1, parts[i]);
    }

    free_split_result(parts, count);

    return 0;
}
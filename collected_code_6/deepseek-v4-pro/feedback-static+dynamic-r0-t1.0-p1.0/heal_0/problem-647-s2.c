#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_uppercase(const char *str, int *count) {
    if (!str || !count) {
        return NULL;
    }

    int len = strlen(str);
    int max_parts = len + 1;
    char **parts = malloc(max_parts * sizeof(char *));
    if (!parts) {
        return NULL;
    }

    int part_count = 0;
    int start = 0;

    for (int i = 0; i <= len; i++) {
        if (i == len || (i > 0 && isupper((unsigned char)str[i]))) {
            int part_len = i - start;
            if (part_len > 0) {
                parts[part_count] = malloc((part_len + 1) * sizeof(char));
                if (!parts[part_count]) {
                    for (int j = 0; j < part_count; j++) {
                        free(parts[j]);
                    }
                    free(parts);
                    return NULL;
                }
                memcpy(parts[part_count], str + start, part_len);
                parts[part_count][part_len] = '\0';
                part_count++;
            }
            start = i;
        }
    }

    char **result = realloc(parts, part_count * sizeof(char *));
    if (!result && part_count > 0) {
        for (int j = 0; j < part_count; j++) {
            free(parts[j]);
        }
        free(parts);
        return NULL;
    }

    *count = part_count;
    return result ? result : parts;
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
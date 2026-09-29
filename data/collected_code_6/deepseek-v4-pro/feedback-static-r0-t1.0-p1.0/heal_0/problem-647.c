#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_uppercase(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    int len = strlen(str);
    if (len == 0) {
        *count = 0;
        char **result = malloc(sizeof(char *));
        if (result == NULL) {
            return NULL;
        }
        result[0] = NULL;
        return result;
    }

    int max_parts = 1;
    for (int i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i])) {
            max_parts++;
        }
    }

    char **parts = malloc((max_parts + 1) * sizeof(char *));
    if (parts == NULL) {
        return NULL;
    }

    int part_index = 0;
    int start = 0;
    int i = 0;

    while (i <= len) {
        if (i == len || (i > 0 && isupper((unsigned char)str[i]))) {
            int part_len = i - start;
            if (part_len > 0) {
                char *part = malloc((part_len + 1) * sizeof(char));
                if (part == NULL) {
                    for (int j = 0; j < part_index; j++) {
                        free(parts[j]);
                    }
                    free(parts);
                    return NULL;
                }
                strncpy(part, str + start, part_len);
                part[part_len] = '\0';
                parts[part_index++] = part;
            }
            start = i;
        }
        i++;
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
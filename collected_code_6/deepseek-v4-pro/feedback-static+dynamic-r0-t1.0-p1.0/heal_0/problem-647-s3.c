#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_uppercase(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    int len = strlen(str);
    int max_parts = len + 1;
    char **result = (char **)malloc(max_parts * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    *count = 0;
    int start = 0;
    int i;

    for (i = 1; i <= len; i++) {
        if (i == len || isupper((unsigned char)str[i])) {
            int part_len = i - start;
            result[*count] = (char *)malloc((part_len + 1) * sizeof(char));
            if (result[*count] == NULL) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strncpy(result[*count], str + start, part_len);
            result[*count][part_len] = '\0';
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
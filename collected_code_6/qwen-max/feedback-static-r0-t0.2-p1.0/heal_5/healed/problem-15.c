#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char **split_string_at_lowercase(const char *input, int *count) {
    *count = 0;
    if (input == NULL || *input == '\0') {
        return NULL;
    }

    const char *start = input;
    int capacity = 100;
    char **result = (char **)malloc(capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    while (*input) {
        if (islower((unsigned char)*input)) {
            size_t len = input - start;
            result[*count] = (char *)malloc(len + 1);
            if (result[*count] == NULL) {
                for (int i = 0; i < *count; i++) {
                    free(result[i]);
                }
                free(result);
                return NULL;
            }
            strncpy(result[*count], start, len);
            result[*count][len] = '\0';
            (*count)++;
            start = input + 1;
        }
        input++;
    }

    if (start != input) {
        size_t len = input - start;
        result[*count] = (char *)malloc(len + 1);
        if (result[*count] == NULL) {
            for (int i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            return NULL;
        }
        strncpy(result[*count], start, len);
        result[*count][len] = '\0';
        (*count)++;
    }

    return result;
}

void free_split_strings(char **strings, int count) {
    for (int i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char *input = "HelloWorldThisIsATest";
    int count;
    char **result = split_string_at_lowercase(input, &count);

    if (result != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", result[i]);
        }
        free_split_strings(result, count);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
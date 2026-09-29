#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char **split_string_at_lowercase(const char *input, int *count) {
    *count = 0;
    if (input == NULL || *input == '\0') {
        return NULL;
    }

    char **result = (char **)malloc(100 * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    const char *start = input;
    while (*input) {
        if (islower((unsigned char)*input)) {
            result[*count] = (char *)malloc(input - start + 1);
            if (result[*count] == NULL) {
                for (int i = 0; i < *count; i++) {
                    free(result[i]);
                }
                free(result);
                return NULL;
            }
            memcpy(result[*count], start, input - start);
            result[*count][input - start] = '\0';
            (*count)++;
            start = input + 1;
        }
        input++;
    }

    if (start != input) {
        result[*count] = (char *)malloc(input - start + 1);
        if (result[*count] == NULL) {
            for (int i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            return NULL;
        }
        memcpy(result[*count], start, input - start);
        result[*count][input - start] = '\0';
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
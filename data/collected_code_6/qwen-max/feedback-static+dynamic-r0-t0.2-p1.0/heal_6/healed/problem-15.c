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
    *count = 1;
    while (*input) {
        if (islower((unsigned char)*input)) {
            (*count)++;
        }
        input++;
    }

    char **result = (char **)malloc(*count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    start = input = input - *count + 1;
    for (int i = 0; i < *count; i++) {
        while (*input && !islower((unsigned char)*input)) {
            input++;
        }
        size_t length = input - start;
        result[i] = (char *)malloc(length + 1);
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        memcpy(result[i], start, length);
        result[i][length] = '\0';
        start = input + 1;
        if (islower((unsigned char)*input)) {
            input++;
        }
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
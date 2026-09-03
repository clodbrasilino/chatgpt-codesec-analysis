#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char **split_string_at_lowercase(const char *input, int *count) {
    int length = strlen(input);
    int capacity = 10;
    char **result = (char **)malloc(capacity * sizeof(char *));
    if (!result) return NULL;

    *count = 0;
    int start = 0;
    for (int i = 0; i <= length; ++i) {
        if (i == length || islower((unsigned char)input[i])) {
            if (i > start) {
                if (*count >= capacity - 1) {
                    capacity *= 2;
                    result = (char **)realloc(result, capacity * sizeof(char *));
                    if (!result) return NULL;
                }
                result[*count] = (char *)malloc((i - start + 1) * sizeof(char));
                if (!result[*count]) {
                    while (*count > 0) free(result[--*count]);
                    free(result);
                    return NULL;
                }
                strncpy(result[*count], &input[start], i - start);
                result[*count][i - start] = '\0';
                (*count)++;
            }
            start = i + 1;
        }
    }
    result[*count] = NULL;
    return result;
}

void free_split_strings(char **strings) {
    if (strings) {
        int i = 0;
        while (strings[i] != NULL) {
            free(strings[i]);
            i++;
        }
        free(strings);
    }
}

int main() {
    const char *input = "HelloWorldThisIsATest";
    int count;
    char **result = split_string_at_lowercase(input, &count);

    if (result) {
        for (int i = 0; i < count; ++i) {
            printf("%s\n", result[i]);
        }
        free_split_strings(result);
    }

    return 0;
}
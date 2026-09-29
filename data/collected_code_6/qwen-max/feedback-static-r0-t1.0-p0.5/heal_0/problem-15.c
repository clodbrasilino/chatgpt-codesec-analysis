#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_string_at_lowercase(const char *input, int *count) {
    int length = strlen(input);
    char **result = (char **)malloc((length + 1) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }
    *count = 0;

    const char *start = input;
    for (int i = 0; i <= length; ++i) {
        if (i == length || islower((unsigned char)input[i])) {
            result[*count] = (char *)malloc((i - (start - input) + 1) * sizeof(char));
            if (result[*count] == NULL) {
                for (int j = 0; j < *count; ++j) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strncpy(result[*count], start, i - (start - input));
            result[*count][i - (start - input)] = '\0';
            (*count)++;
            start = input + i + 1;
        }
    }

    result[*count] = NULL;
    return result;
}

void free_split_strings(char **strings) {
    if (strings != NULL) {
        for (int i = 0; strings[i] != NULL; ++i) {
            free(strings[i]);
        }
        free(strings);
    }
}

int main() {
    const char *input = "AbCdEfGhIjK";
    int count;
    char **result = split_string_at_lowercase(input, &count);

    if (result != NULL) {
        for (int i = 0; i < count; ++i) {
            printf("%s\n", result[i]);
        }
        free_split_strings(result);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    return 0;
}
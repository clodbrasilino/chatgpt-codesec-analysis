#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char **split_string(const char *input, int *count) {
    int length = strlen(input);
    char **result = (char **)malloc((length + 1) * sizeof(char *));
    if (result == NULL) return NULL;
    *count = 0;

    const char *start = input;
    for (int i = 0; i <= length; ++i) {
        if (i == length || islower((unsigned char)input[i])) {
            if (start < &input[i]) {
                result[*count] = (char *)malloc((i - (start - input) + 1) * sizeof(char));
                if (result[*count] == NULL) {
                    for (int j = 0; j < *count; ++j) free(result[j]);
                    free(result);
                    return NULL;
                }
                memcpy(result[*count], start, i - (start - input));
                result[*count][i - (start - input)] = '\0';
                (*count)++;
            }
            start = &input[i] + 1;
        }
    }

    return result;
}

void free_split_strings(char **strings, int count) {
    for (int i = 0; i < count; ++i) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char *input = "aBCdEfGHiJKL";
    int count;
    char **result = split_string(input, &count);

    if (result != NULL) {
        for (int i = 0; i < count; ++i) {
            printf("%s\n", result[i]);
        }
        free_split_strings(result, count);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
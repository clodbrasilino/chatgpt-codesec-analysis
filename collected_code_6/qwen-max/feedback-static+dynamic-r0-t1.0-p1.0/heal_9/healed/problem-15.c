#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char **split_string(const char *input, int *count) {
    size_t length = strlen(input);
    char **result = (char **)malloc((length / 2 + 2) * sizeof(char *));
    if (result == NULL) return NULL;
    *count = 0;

    const char *start = input;
    for (size_t i = 0; i <= length; ++i) {
        if (i == length || !islower((unsigned char)input[i])) {
            if (start < &input[i]) {
                size_t segment_length = i - (size_t)(start - input);
                result[*count] = (char *)malloc((segment_length + 1) * sizeof(char));
                if (result[*count] == NULL) {
                    while (*count > 0) free(result[--*count]);
                    free(result);
                    return NULL;
                }
                memcpy(result[*count], start, segment_length);
                result[*count][segment_length] = '\0';
                (*count)++;
            }
            if (i < length) start = &input[i + 1];
        }
    }

    result[*count] = NULL;
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
        for (int i = 0; result[i] != NULL; ++i) {
            printf("%s\n", result[i]);
        }
        free_split_strings(result, count);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
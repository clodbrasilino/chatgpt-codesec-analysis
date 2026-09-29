#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings(const char *const *input, size_t count, size_t min_size, size_t *output_count) {
    *output_count = 0;
    if (count == 0) return NULL;

    char **result = (char **)malloc((count + 1) * sizeof(char *));
    if (result == NULL) return NULL;

    for (size_t i = 0; i < count; ++i) {
        size_t input_len = strlen(input[i]);
        if (input_len >= min_size) {
            result[*output_count] = (char *)malloc((input_len + 1) * sizeof(char));
            if (result[*output_count] == NULL) {
                while (*output_count > 0) free(result[--(*output_count)]);
                free(result);
                return NULL;
            }
            strcpy(result[*output_count], input[i]);
            (*output_count)++;
        }
    }
    result[*output_count] = NULL;
    return result;
}

void free_strings(char **strings) {
    if (strings == NULL) return;
    for (size_t i = 0; strings[i] != NULL; ++i) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char *input[] = {"practice", "solution", "Python", "exercises"};
    size_t count = sizeof(input) / sizeof(input[0]);
    size_t min_size = 3;
    size_t output_count = 0;

    char **result = extract_strings(input, count, min_size, &output_count);

    if (result != NULL) {
        for (size_t i = 0; i < output_count; ++i) {
            printf("%s\n", result[i]);
        }
        free_strings(result);
    } else {
        printf("Failed to allocate memory.\n");
    }

    return 0;
}
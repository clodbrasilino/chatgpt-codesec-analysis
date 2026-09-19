#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings(const char *const *input, size_t count, size_t size, size_t *output_count) {
    if (input == NULL || output_count == NULL) return NULL;
    *output_count = 0;

    for (size_t i = 0; i < count; ++i) {
        if (strlen(input[i]) >= size) (*output_count)++;
    }

    if (*output_count == 0) return NULL;

    char **result = (char **)malloc(*output_count * sizeof(char *));
    if (result == NULL) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < count; ++i) {
        if (strlen(input[i]) >= size) {
            result[j] = (char *)malloc(strlen(input[i]) + 1);
            if (result[j] == NULL) {
                while (j > 0) free(result[--j]);
                free(result);
                return NULL;
            }
            strcpy(result[j], input[i]);
            j++;
        }
    }

    return result;
}

int main() {
    const char *input[] = {"practice", "solution", "exercises", "Python", "C programming"};
    size_t count = 5;
    size_t size = 5;
    size_t output_count = 0;

    char **result = extract_strings(input, count, size, &output_count);

    if (result != NULL) {
        for (size_t i = 0; i < output_count; ++i) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}
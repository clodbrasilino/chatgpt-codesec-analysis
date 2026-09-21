#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings(const char *const *input, size_t count, size_t size, size_t *output_count) {
    if (!input || !output_count) return NULL;
    *output_count = 0;

    for (size_t i = 0; i < count; ++i) {
        size_t len = strlen(input[i]);
        if (len >= size - 1) continue;
        (*output_count)++;
    }

    char **result = (char **)malloc(*output_count * sizeof(char *));
    if (!result) return NULL;

    *output_count = 0;
    for (size_t i = 0; i < count; ++i) {
        size_t len = strlen(input[i]);
        if (len >= size - 1) continue;
        result[*output_count] = (char *)malloc(size);
        if (!result[*output_count]) {
            while (*output_count > 0) free(result[--*output_count]);
            free(result);
            return NULL;
        }
        memcpy(result[*output_count], input[i], len);
        result[*output_count][len] = '\0';
        (*output_count)++;
    }

    return result;
}

int main() {
    const char *input[] = {"practice", "solution", "Python", "exercises", "C programming"};
    size_t count = 5;
    size_t size = 7;
    size_t output_count;

    char **result = extract_strings(input, count, size, &output_count);

    if (result) {
        for (size_t i = 0; i < output_count; ++i) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}
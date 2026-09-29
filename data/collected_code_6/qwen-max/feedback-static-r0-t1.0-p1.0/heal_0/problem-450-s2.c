#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_strings(const char* const* input, size_t count, size_t size, size_t* output_count) {
    *output_count = 0;
    char** result = (char**)malloc(count * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < count; ++i) {
        if (strlen(input[i]) <= size) {
            result[(*output_count)] = (char*)malloc((size + 1) * sizeof(char));
            if (result[(*output_count)] == NULL) {
                for (size_t j = 0; j < *output_count; ++j) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strncpy(result[(*output_count)], input[i], size);
            result[(*output_count)][size] = '\0';
            (*output_count)++;
        }
    }
    return result;
}

void free_strings(char** strings, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char* const input[] = {"hello", "world", "short", "verylongstring", "tiny"};
    size_t count = sizeof(input) / sizeof(input[0]);
    size_t size = 5;
    size_t output_count;

    char** extracted = extract_strings(input, count, size, &output_count);
    if (extracted != NULL) {
        for (size_t i = 0; i < output_count; ++i) {
            printf("%s\n", extracted[i]);
        }
        free_strings(extracted, output_count);
    }

    return 0;
}
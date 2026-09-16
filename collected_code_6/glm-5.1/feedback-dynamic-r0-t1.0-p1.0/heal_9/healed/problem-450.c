#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_substrings(const char** strings, size_t count, size_t size, size_t* result_count) {
    if (strings == NULL || result_count == NULL || size == 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL && strlen(strings[i]) >= size) {
            valid_count++;
        }
    }

    if (valid_count == 0) {
        *result_count = 0;
        return NULL;
    }

    char** result = (char**)malloc(valid_count * sizeof(char*));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    size_t current_index = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL && strlen(strings[i]) >= size) {
            result[current_index] = (char*)malloc((size + 1) * sizeof(char));
            if (result[current_index] == NULL) {
                for (size_t j = 0; j < current_index; j++) {
                    free(result[j]);
                }
                free(result);
                *result_count = 0;
                return NULL;
            }
            strncpy(result[current_index], strings[i], size);
            result[current_index][size] = '\0';
            current_index++;
        }
    }

    *result_count = valid_count;
    return result;
}

void free_substrings(char** strings, size_t count) {
    if (strings == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char* input_strings[] = {
        "Python",
        "practice",
        "solution",
        "exercises"
    };
    size_t count = sizeof(input_strings) / sizeof(input_strings[0]);
    size_t result_count = 0;
    size_t sizes[] = {6, 8, 9};
    size_t num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (size_t s = 0; s < num_sizes; s++) {
        size_t current_size = sizes[s];
        char** extracted = extract_substrings(input_strings, count, current_size, &result_count);
        if (extracted != NULL && result_count > 0) {
            for (size_t i = 0; i < result_count; i++) {
                printf("%s\n", extracted[i]);
            }
            free_substrings(extracted, result_count);
        }
    }

    return 0;
}
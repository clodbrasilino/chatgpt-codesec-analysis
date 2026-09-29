#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings_by_length(const char **strings, size_t count, size_t target_length, size_t *out_count) {
    if (!strings || !out_count) {
        return NULL;
    }

    size_t match_count = 0;
    for (size_t i = 0; i < count; ++i) {
        if (strings[i] && strnlen(strings[i], target_length + 1) == target_length) {
            match_count++;
        }
    }

    *out_count = match_count;
    if (match_count == 0) {
        return NULL;
    }

    char **result = (char **)malloc(match_count * sizeof(char *));
    if (!result) {
        *out_count = 0;
        return NULL;
    }

    size_t result_idx = 0;
    for (size_t i = 0; i < count; ++i) {
        if (strings[i] && strnlen(strings[i], target_length + 1) == target_length) {
            result[result_idx] = (char *)malloc(target_length + 1);
            if (!result[result_idx]) {
                for (size_t j = 0; j < result_idx; ++j) {
                    free(result[j]);
                }
                free(result);
                *out_count = 0;
                return NULL;
            }
            
            memcpy(result[result_idx], strings[i], target_length + 1);
            result_idx++;
        }
    }

    return result;
}

void free_extracted_strings(char **strings, size_t count) {
    if (!strings) {
        return;
    }
    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }
    free(strings);
}

int main(void) {
    const char *input_strings[] = {
        "apple",
        "cat",
        "banana",
        "dog",
        "elephant",
        "fox"
    };
    
    size_t input_count = sizeof(input_strings) / sizeof(input_strings[0]);
    size_t target_len = 3;
    size_t extracted_count = 0;

    char **extracted = extract_strings_by_length(input_strings, input_count, target_len, &extracted_count);

    if (extracted) {
        for (size_t i = 0; i < extracted_count; ++i) {
            if (printf("%s\n", extracted[i]) < 0) {
                free_extracted_strings(extracted, extracted_count);
                return EXIT_FAILURE;
            }
        }
        free_extracted_strings(extracted, extracted_count);
    }

    return EXIT_SUCCESS;
}
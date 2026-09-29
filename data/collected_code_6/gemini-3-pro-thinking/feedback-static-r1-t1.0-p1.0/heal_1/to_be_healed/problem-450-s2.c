#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings_by_length(const char **strings, size_t count, size_t target_length, size_t *out_count) {
    if (!strings || !out_count) {
        return NULL;
    }

    size_t match_count = 0;
    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strings[i] && strlen(strings[i]) == target_length) {
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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strings[i] && strlen(strings[i]) == target_length) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(strings[i]);
            result[result_idx] = (char *)malloc(len + 1);
            if (!result[result_idx]) {
                for (size_t j = 0; j < result_idx; ++j) {
                    free(result[j]);
                }
                free(result);
                *out_count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[result_idx], strings[i], len + 1);
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
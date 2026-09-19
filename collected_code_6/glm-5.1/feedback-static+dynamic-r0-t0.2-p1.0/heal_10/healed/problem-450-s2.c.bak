#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_substrings(const char** strings, size_t count, size_t n, size_t* out_count) {
    if (strings == NULL || count == 0 || n == 0) {
        if (out_count) *out_count = 0;
        return NULL;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL && strlen(strings[i]) >= n) {
            valid_count++;
        }
    }

    if (valid_count == 0) {
        if (out_count) *out_count = 0;
        return NULL;
    }

    char** result = (char**)malloc(valid_count * sizeof(char*));
    if (result == NULL) {
        if (out_count) *out_count = 0;
        return NULL;
    }

    size_t res_idx = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL && strlen(strings[i]) >= n) {
            result[res_idx] = (char*)malloc((n + 1) * sizeof(char));
            if (result[res_idx] == NULL) {
                for (size_t j = 0; j < res_idx; j++) {
                    free(result[j]);
                }
                free(result);
                if (out_count) *out_count = 0;
                return NULL;
            }
            strncpy(result[res_idx], strings[i], n);
            result[res_idx][n] = '\0';
            res_idx++;
        }
    }

    if (out_count) *out_count = res_idx;
    return result;
}

void free_extracted_strings(char** strings, size_t count) {
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main(void) {
    const char* input_strings[] = {
        "Python",
        "list",
        "exercises",
        "practice",
        "solution",
        NULL
    };

    size_t count = 0;
    if (input_strings != NULL) {
        while (input_strings[count] != NULL) {
            count++;
        }
    }

    size_t extract_n[] = {8, 6, 9};
    size_t num_tests = sizeof(extract_n) / sizeof(extract_n[0]);

    for (size_t t = 0; t < num_tests; t++) {
        size_t extracted_count = 0;
        char** extracted = extract_substrings(input_strings, count, extract_n[t], &extracted_count);
        if (extracted != NULL) {
            for (size_t i = 0; i < extracted_count; i++) {
                printf("%s\n", extracted[i]);
            }
            free_extracted_strings(extracted, extracted_count);
        }
    }

    return EXIT_SUCCESS;
}
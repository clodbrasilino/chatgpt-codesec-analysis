#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  */

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

    char** result = (char**)malloc((valid_count + 1) * sizeof(char*));
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

    result[res_idx] = NULL;
    if (out_count) *out_count = valid_count;
    return result;
}

void free_extracted_strings(char** strings) {
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; strings[i] != NULL; i++) {
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
    while (input_strings[count] != NULL) {
        count++;
    }

    size_t extract_size = 8;

    size_t extracted_count = 0;
    char** extracted = extract_substrings(input_strings, count, extract_size, &extracted_count);
    if (extracted == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < extracted_count; i++) {
        printf("%s\n", extracted[i]);
    }

    free_extracted_strings(extracted);

    return EXIT_SUCCESS;
}
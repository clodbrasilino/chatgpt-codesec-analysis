#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  */

char** extract_substrings(char** strings, size_t count, size_t size, size_t* out_count) {
    if (strings == NULL || out_count == NULL || size == 0) {
        return NULL;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < count; ++i) {
        if (strings[i] != NULL) {
            size_t len = 0;
            while (strings[i][len] != '\0' && len < size) {
                len++;
            }
            if (len >= size) {
                valid_count++;
            }
        }
    }

    if (valid_count == 0) {
        *out_count = 0;
        return NULL;
    }

    char** result = (char**)malloc(valid_count * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    for (size_t i = 0; i < count; ++i) {
        if (strings[i] != NULL) {
            size_t len = 0;
            while (strings[i][len] != '\0' && len < size) {
                len++;
            }
            if (len >= size) {
                result[res_idx] = (char*)malloc((size + 1) * sizeof(char));
                if (result[res_idx] == NULL) {
                    for (size_t j = 0; j < res_idx; ++j) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[res_idx], strings[i], size);
                result[res_idx][size] = '\0';
                res_idx++;
            }
        }
    }

    *out_count = valid_count;
    return result;
}

int main(void) {
    char* input[] = {
        "practice",
        "solution",
        "Python",
        "exercises"
    };

    size_t input_count = sizeof(input) / sizeof(input[0]);
    size_t extract_size = 6;
    size_t out_count = 0;

    char** extracted = extract_substrings(input, input_count, extract_size, &out_count);

    if (extracted != NULL) {
        for (size_t i = 0; i < out_count; ++i) {
            printf("%s\n", extracted[i]);
            free(extracted[i]);
        }
        free(extracted);
    }

    return 0;
}
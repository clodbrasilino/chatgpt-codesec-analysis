#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  */

char** extract_strings(const char* const* input, size_t count, size_t size, size_t* output_count) {
    *output_count = 0;
    char** result = (char**)malloc(count * sizeof(char*));
    if (!result) {
        return NULL;
    }
    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input[i]);
        if (len <= size) {
            result[*output_count] = (char*)malloc((len + 1) * sizeof(char));
            if (!result[*output_count]) {
                for (size_t j = 0; j < *output_count; ++j) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[*output_count], input[i], len);
            result[*output_count][len] = '\0';
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
    if (extracted) {
        for (size_t i = 0; i < output_count; ++i) {
            printf("%s\n", extracted[i]);
        }
        free_strings(extracted, output_count);
    }

    return 0;
}
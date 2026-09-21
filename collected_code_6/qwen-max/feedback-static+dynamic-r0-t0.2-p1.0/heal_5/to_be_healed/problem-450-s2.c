#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  */

char **extract_strings(const char *const *source, size_t source_count, size_t size, size_t *result_count) {
    char **result = (char **)malloc(source_count * sizeof(char *));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    for (size_t i = 0; i < source_count; ++i) {
        size_t len = strnlen(source[i], size + 1);
        if (len > size) {
            result[i] = (char *)malloc(size + 1);
            if (result[i] == NULL) {
                for (size_t j = 0; j < i; ++j) {
                    free(result[j]);
                }
                free(result);
                *result_count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result[i], source[i], size);
            result[i][size] = '\0';
        } else {
            result[i] = (char *)malloc(len + 1);
            if (result[i] == NULL) {
                for (size_t j = 0; j < i; ++j) {
                    free(result[j]);
                }
                free(result);
                *result_count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[i], source[i], len);
            result[i][len] = '\0';
        }
    }

    *result_count = source_count;
    return result;
}

int main() {
    const char *source[] = {"practice", "solution", "Python", "exercises"};
    size_t source_count = sizeof(source) / sizeof(source[0]);
    size_t size = 7;
    size_t result_count;

    char **result = extract_strings(source, source_count, size, &result_count);

    if (result != NULL) {
        for (size_t i = 0; i < result_count; ++i) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}
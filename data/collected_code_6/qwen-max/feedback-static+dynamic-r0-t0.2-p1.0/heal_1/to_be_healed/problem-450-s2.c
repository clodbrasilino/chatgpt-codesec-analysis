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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(source[i]) >= size) {
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
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            result[i] = (char *)malloc(strlen(source[i]) + 1);
            if (result[i] == NULL) {
                for (size_t j = 0; j < i; ++j) {
                    free(result[j]);
                }
                free(result);
                *result_count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(result[i], source[i]);
        }
    }

    *result_count = source_count;
    return result;
}

int main() {
    const char *source[] = {"hello", "world", "C", "programming"};
    size_t source_count = sizeof(source) / sizeof(source[0]);
    size_t size = 5;
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
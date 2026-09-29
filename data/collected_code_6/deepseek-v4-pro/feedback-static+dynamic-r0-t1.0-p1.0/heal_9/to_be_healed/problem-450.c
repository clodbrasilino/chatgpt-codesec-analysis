#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  */

static char **extract_strings(const char *const *input, size_t count) {
    if (input == NULL || count == 0) {
        return NULL;
    }

    char **result = calloc(count, sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        if (input[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input[i]);
        if (len >= count * 256) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        result[i] = malloc(len + 1);
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i], input[i], len + 1);
    }

    return result;
}

int main(void) {
    const char *strings[] = {"practice", "solution", "Python", "exercises"};
    size_t count = sizeof(strings) / sizeof(strings[0]);

    char **extracted = extract_strings(strings, count);
    if (extracted == NULL) {
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", extracted[i]);
        free(extracted[i]);
    }

    free(extracted);
    return 0;
}
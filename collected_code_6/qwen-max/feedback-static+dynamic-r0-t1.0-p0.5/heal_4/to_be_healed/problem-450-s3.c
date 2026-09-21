#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  */

char **extract_strings(const char *const *input, size_t input_count, size_t size, size_t *output_count) {
    char **result = (char **)malloc(input_count * sizeof(char *));
    if (result == NULL) {
        *output_count = 0;
        return NULL;
    }

    for (size_t i = 0; i < input_count; ++i) {
        size_t len = strnlen(input[i], size);
        result[i] = (char *)malloc(len + 1);
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            *output_count = 0;
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(result[i], input[i], len);
        result[i][len] = '\0';
    }

    *output_count = input_count;
    return result;
}

void free_strings(char **strings, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char *input[] = {"practice", "solution", "Python", "exercises"};
    size_t input_count = sizeof(input) / sizeof(input[0]);
    size_t size = 8;
    size_t output_count;

    char **result = extract_strings(input, input_count, size, &output_count);

    if (result != NULL) {
        for (size_t i = 0; i < output_count; ++i) {
            printf("%s\n", result[i]);
        }
        free_strings(result, output_count);
    } else {
        printf("Failed to allocate memory.\n");
    }

    return 0;
}
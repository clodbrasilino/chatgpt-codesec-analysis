#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  */

char** extract_strings(const char* const strings[], size_t num_strings, size_t size, size_t* out_num_strings) {
    *out_num_strings = 0;
    if (strings == NULL || num_strings == 0 || size == 0) {
        return NULL;
    }

    char** result = (char**)malloc(num_strings * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < num_strings; ++i) {
        if (strings[i] != NULL) {
            size_t len = strnlen(strings[i], size);
            if (len >= size) {
                len = size - 1;
            }
            result[i] = (char*)malloc((len + 1) * sizeof(char));
            if (result[i] == NULL) {
                for (size_t j = 0; j < i; ++j) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result[i], strings[i], len);
            result[i][len] = '\0';
            (*out_num_strings)++;
        }
    }

    return result;
}

int main() {
    const char* const input_strings[] = {"practice", "solution", "exercises", "Python"};
    size_t num_input_strings = sizeof(input_strings) / sizeof(input_strings[0]);
    size_t size = 8;
    size_t num_output_strings;

    char** output_strings = extract_strings(input_strings, num_input_strings, size, &num_output_strings);

    if (output_strings != NULL) {
        for (size_t i = 0; i < num_output_strings; ++i) {
            printf("%s\n", output_strings[i]);
            free(output_strings[i]);
        }
        free(output_strings);
    }

    return 0;
}
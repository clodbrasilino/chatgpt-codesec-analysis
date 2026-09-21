#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  */

char **extract_strings(const char *const *input, size_t input_count, size_t size, size_t *output_count) {
    *output_count = 0;
    char **output = (char **)malloc(input_count * sizeof(char *));
    if (output == NULL) return NULL;

    for (size_t i = 0; i < input_count; ++i) {
        size_t len = strnlen(input[i], size + 1);
        if (len >= size) {
            output[*output_count] = (char *)malloc(size + 1);
            if (output[*output_count] == NULL) {
                while (*output_count > 0) {
                    free(output[(*output_count) - 1]);
                    (*output_count)--;
                }
                free(output);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output[*output_count], input[i], size);
            output[*output_count][size] = '\0';
            (*output_count)++;
        } else {
            output[*output_count] = (char *)malloc(len + 1);
            if (output[*output_count] == NULL) {
                while (*output_count > 0) {
                    free(output[(*output_count) - 1]);
                    (*output_count)--;
                }
                free(output);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output[*output_count], input[i], len);
            output[*output_count][len] = '\0';
            (*output_count)++;
        }
    }

    return output;
}

int main() {
    const char *input[] = {"practice", "solution", "Python", "exercises"};
    size_t input_count = sizeof(input) / sizeof(input[0]);
    size_t size = 9;
    size_t output_count = 0;

    char **output = extract_strings(input, input_count, size, &output_count);

    if (output != NULL) {
        for (size_t i = 0; i < output_count; ++i) {
            printf("%s\n", output[i]);
            free(output[i]);
        }
        free(output);
    }

    return 0;
}
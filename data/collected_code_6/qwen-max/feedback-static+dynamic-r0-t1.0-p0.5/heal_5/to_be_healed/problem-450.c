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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(input[i]) >= size) {
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
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(output[*output_count], input[i], size);
            output[*output_count][size] = '\0';
            (*output_count)++;
        } else {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            output[*output_count] = (char *)malloc(strlen(input[i]) + 1);
            if (output[*output_count] == NULL) {
                while (*output_count > 0) {
                    free(output[(*output_count) - 1]);
                    (*output_count)--;
                }
                free(output);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(output[*output_count], input[i]);
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *abbreviate_road(const char *input, size_t input_len)
{
    static const char target[] = "road";
    static const char replacement[] = "rd.";
    const size_t target_len = sizeof(target) - 1;
    const size_t replacement_len = sizeof(replacement) - 1;
    size_t occurrences = 0;
    size_t output_len;
    size_t i;
    size_t j;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    for (i = 0; i + target_len <= input_len;) {
        if (memcmp(input + i, target, target_len) == 0) {
            ++occurrences;
            i += target_len;
        } else {
            ++i;
        }
    }

    if (occurrences > input_len / (target_len - replacement_len)) {
        return NULL;
    }

    output_len = input_len -
                 occurrences * (target_len - replacement_len);

    if (output_len == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_len + 1);
    if (output == NULL) {
        return NULL;
    }

    i = 0;
    j = 0;

    while (i < input_len) {
        if (i + target_len <= input_len &&
            memcmp(input + i, target, target_len) == 0) {
            if (replacement_len > output_len - j) {
                free(output);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + j, replacement, replacement_len);
            i += target_len;
            j += replacement_len;
        } else {
            if (j >= output_len) {
                free(output);
                return NULL;
            }

            output[j++] = input[i++];
        }
    }

    output[j] = '\0';
    return output;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;
    char *result;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        char *new_input;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return EXIT_SUCCESS;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    result = abbreviate_road(input, length);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
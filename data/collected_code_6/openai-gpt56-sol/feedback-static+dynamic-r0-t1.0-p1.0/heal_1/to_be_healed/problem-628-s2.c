#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int replace_spaces(const char *input, char **output)
{
    size_t length;
    size_t spaces = 0;
    size_t output_length;
    size_t i;
    size_t j = 0;
    char *result;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(input);

    for (i = 0; i < length; ++i) {
        if (input[i] == ' ') {
            ++spaces;
        }
    }

    if (spaces > (SIZE_MAX - length - 1) / 2) {
        return -1;
    }

    output_length = length + (spaces * 2);
    result = malloc(output_length + 1);

    if (result == NULL) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        if (input[i] == ' ') {
            result[j++] = '%';
            result[j++] = '2';
            result[j++] = '0';
        } else {
            result[j++] = input[i];
        }
    }

    result[j] = '\0';
    *output = result;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    char *output = NULL;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    if (replace_spaces(input, &output) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}
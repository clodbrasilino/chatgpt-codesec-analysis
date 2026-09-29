#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_multiple(const char *input, char target)
{
    size_t len;
    size_t i;
    size_t j;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    result = malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    j = 0U;
    for (i = 0U; i < len; i++) {
        result[j] = input[i];
        j++;
        if (input[i] == target) {
            while ((i + 1U) < len && input[i + 1U] == target) {
                i++;
            }
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *text = "aaabbbcccaaadddaaa";
    char *output;

    output = replace_multiple(text, 'a');
    if (output == NULL) {
        (void)fprintf(stderr, "Error: could not process string\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", text) < 0) {
        free(output);
        return EXIT_FAILURE;
    }
    if (printf("Result:   %s\n", output) < 0) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}
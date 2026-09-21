#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_multiple_spaces(const char *input);

char *remove_multiple_spaces(const char *input)
{
    char *output;
    size_t len;
    size_t i;
    size_t j;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len == (size_t)-1) {
        return NULL;
    }

    output = malloc(len + 1U);
    if (output == NULL) {
        return NULL;
    }

    j = 0U;
    for (i = 0U; i < len; i++) {
        if (input[i] == ' ' && j > 0U && output[j - 1U] == ' ') {
            continue;
        }
        output[j] = input[i];
        j++;
    }
    output[j] = '\0';

    return output;
}

int main(void)
{
    const char *test = "This   is  a    string   with     multiple spaces.";
    char *result;

    result = remove_multiple_spaces(test);
    if (result == NULL) {
        fprintf(stderr, "Failed to process the string.\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", test) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    if (printf("Cleaned:  %s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
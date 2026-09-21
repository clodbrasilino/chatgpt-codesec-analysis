#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index_chars(const char *input);

char *remove_odd_index_chars(const char *input)
{
    size_t len;
    size_t result_len;
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
    result_len = (len / 2U) + (len % 2U);

    result = malloc(result_len + 1U);
    if (result == NULL) {
        return NULL;
    }

    j = 0U;
    for (i = 0U; i < len; i += 2U) {
        result[j] = input[i];
        j++;
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "abcdef",
        "hello world",
        "a",
        ""
    };
    size_t count;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'output' can be reduced. [variableScope]
     */
    char *output;

    count = sizeof(test_strings) / sizeof(test_strings[0]);

    for (i = 0U; i < count; i++) {
        output = remove_odd_index_chars(test_strings[i]);
        if (output == NULL) {
            fprintf(stderr, "Error: failed to process string\n");
            return EXIT_FAILURE;
        }
        if (printf("Input: \"%s\" -> Output: \"%s\"\n",
                   test_strings[i], output) < 0) {
            free(output);
            return EXIT_FAILURE;
        }
        free(output);
        output = NULL;
    }

    return EXIT_SUCCESS;
}
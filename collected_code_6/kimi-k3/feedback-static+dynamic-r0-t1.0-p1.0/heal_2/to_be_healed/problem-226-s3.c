#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index_chars(const char *input, size_t max_len)
{
    if (input == NULL) {
        return NULL;
    }

    size_t len = strnlen(input, max_len);
    size_t output_len = (len + 1) / 2;

    char *result = (char *)malloc(output_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i += 2) {
        result[j++] = input[i];
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *test_string = "Hello, World!";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *result = remove_odd_index_chars(test_string, strlen(test_string) + 1);

    if (result == NULL) {
        fprintf(stderr, "Error: Failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Result:   %s\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}
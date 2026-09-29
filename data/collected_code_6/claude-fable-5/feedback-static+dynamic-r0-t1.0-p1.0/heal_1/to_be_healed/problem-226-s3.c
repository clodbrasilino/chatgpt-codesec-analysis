#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index_chars(const char *input)
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
    result = malloc((len / 2U) + 2U);
    if (result == NULL) {
        return NULL;
    }

    j = 0U;
    for (i = 0U; i < len; i++) {
        if ((i % 2U) == 0U) {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *original = "abcdefghij";
    char *filtered;

    filtered = remove_odd_index_chars(original);
    if (filtered == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", original);
    printf("Filtered: %s\n", filtered);

    free(filtered);
    filtered = NULL;

    return EXIT_SUCCESS;
}
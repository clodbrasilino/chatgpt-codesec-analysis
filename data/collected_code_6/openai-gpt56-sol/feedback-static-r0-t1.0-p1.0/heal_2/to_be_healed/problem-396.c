#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int starts_and_ends_with_same_character(const char *string, int *result)
{
    size_t length;

    if (string == NULL || result == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(string);
    *result = length > 0 && string[0] == string[length - 1];

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    int result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    while (length > 0 &&
           (input[length - 1] == '\n' || input[length - 1] == '\r')) {
        input[--length] = '\0';
    }

    if (starts_and_ends_with_same_character(input, &result) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    puts(result ? "Yes" : "No");
    free(input);

    return EXIT_SUCCESS;
}
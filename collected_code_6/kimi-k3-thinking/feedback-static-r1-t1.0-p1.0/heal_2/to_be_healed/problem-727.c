#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_non_alphanumeric(const char *input)
{
    char *result;
    size_t result_len = 0;
    const unsigned char *cursor;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    result = malloc(strlen(input) + 1);
    if (result == NULL) {
        return NULL;
    }

    cursor = (const unsigned char *)input;
    while (*cursor != '\0') {
        if (isalnum(*cursor)) {
            result[result_len] = (char)*cursor;
            result_len++;
        }
        cursor++;
    }

    result[result_len] = '\0';
    return result;
}

int main(void)
{
    const char *test = "Hello, World! 123 @#$% C-Programming_2024";
    char *cleaned = remove_non_alphanumeric(test);

    if (cleaned == NULL) {
        fprintf(stderr, "Error: string processing failed\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);
    return EXIT_SUCCESS;
}
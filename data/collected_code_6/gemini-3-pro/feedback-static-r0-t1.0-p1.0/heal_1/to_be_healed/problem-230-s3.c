#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* replace_spaces(const char *input, char replacement) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char *result = (char *)malloc(len + 1);

    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        if (input[i] == ' ') {
            result[i] = replacement;
        } else {
            result[i] = input[i];
        }
    }
    result[len] = '\0';

    return result;
}

int main(void) {
    const char *original = "Hello World! This is a test string.";
    char replacement_char = '-';

    char *modified = replace_spaces(original, replacement_char);

    if (modified != NULL) {
        printf("Original: %s\n", original);
        printf("Modified: %s\n", modified);
        free(modified);
    } else {
        fprintf(stderr, "Error: Memory allocation failed or input was NULL.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
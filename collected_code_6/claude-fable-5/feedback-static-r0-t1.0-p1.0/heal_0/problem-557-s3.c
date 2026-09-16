#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *toggle_case(const char *input)
{
    size_t len;
    size_t i;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strlen(input);
    result = malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < len; i++) {
        unsigned char c = (unsigned char)input[i];
        if (isupper(c)) {
            result[i] = (char)tolower(c);
        } else if (islower(c)) {
            result[i] = (char)toupper(c);
        } else {
            result[i] = (char)c;
        }
    }
    result[len] = '\0';

    return result;
}

int main(void)
{
    const char *original = "Hello, World! 123 abcXYZ";
    char *toggled;

    toggled = toggle_case(original);
    if (toggled == NULL) {
        if (fprintf(stderr, "Error: failed to toggle case\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", original) < 0) {
        free(toggled);
        return EXIT_FAILURE;
    }

    if (printf("Toggled:  %s\n", toggled) < 0) {
        free(toggled);
        return EXIT_FAILURE;
    }

    free(toggled);
    return EXIT_SUCCESS;
}
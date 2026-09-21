#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* convert_to_lowercase(const char* input_string) {
    if (input_string == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input_string);
    char* lower_string = (char*)malloc((len + 1) * sizeof(char));

    if (lower_string == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; ++i) {
        lower_string[i] = (char)tolower((unsigned char)input_string[i]);
    }
    lower_string[len] = '\0';

    return lower_string;
}

int main(void) {
    const char* original_string = "Hello World! 123";
    char* lower_string = convert_to_lowercase(original_string);

    if (lower_string != NULL) {
        printf("Original: %s\n", original_string);
        printf("Lowercase: %s\n", lower_string);
        free(lower_string);
    } else {
        printf("Memory allocation failed or input was NULL.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
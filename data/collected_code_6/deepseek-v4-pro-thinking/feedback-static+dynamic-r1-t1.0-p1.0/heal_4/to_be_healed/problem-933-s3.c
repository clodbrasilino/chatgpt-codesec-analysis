#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);

    size_t underscore_count = 0;
    for (size_t i = 1; i < length; i++) {
        if (isupper((unsigned char)input[i])) {
            underscore_count++;
        }
    }

    size_t output_size = length + underscore_count + 1;
    char *output = malloc(output_size);
    if (output == NULL) {
        return NULL;
    }

    size_t out_idx = 0;
    for (size_t i = 0; i < length; i++) {
        if (isupper((unsigned char)input[i])) {
            if (i > 0) {
                output[out_idx++] = '_';
            }
            output[out_idx++] = (char)tolower((unsigned char)input[i]);
        } else {
            output[out_idx++] = input[i];
        }
    }
    output[out_idx] = '\0';

    return output;
}

int main(void) {
    const char *camel = "camelCaseString";
    char *snake = camel_to_snake(camel);

    if (snake != NULL) {
        printf("%s\n", snake);
        free(snake);
    }

    return 0;
}
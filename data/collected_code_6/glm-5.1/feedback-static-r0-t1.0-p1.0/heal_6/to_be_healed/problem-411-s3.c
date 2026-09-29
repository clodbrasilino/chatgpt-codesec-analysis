#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t i = 0;
    const char *cursor = snake_str;

    while (*cursor) {
        if (*cursor == '_') {
            cursor++;
            if (*cursor) {
                camel_str[i++] = toupper((unsigned char)*cursor);
                cursor++;
            }
        } else {
            camel_str[i++] = *cursor++;
        }
    }

    camel_str[i] = '\0';

    return camel_str;
}

int main(void) {
    const char *input = "convert_this_snake_case_string";
    char *output = snake_to_camel(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Conversion failed\n");
        return 1;
    }

    return 0;
}
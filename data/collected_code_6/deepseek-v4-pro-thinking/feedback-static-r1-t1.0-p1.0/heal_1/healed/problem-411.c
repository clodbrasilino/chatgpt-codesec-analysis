#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *output = malloc(len + 1);
    if (output == NULL) {
        return NULL;
    }

    const char *p = input;
    char *q = output;

    while (*p != '\0') {
        if (*p == '_') {
            const char *look = p;
            while (*look == '_') {
                look++;
            }
            if (isalpha((unsigned char)*look)) {
                p = look;
                *q++ = (char)toupper((unsigned char)*p);
                p++;
            } else {
                *q++ = *p++;
            }
        } else {
            *q++ = *p++;
        }
    }

    *q = '\0';
    return output;
}

int main(void)
{
    const char *input = "snake_case_string";
    char *result = snake_to_camel(input);

    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);
    free(result);
    return EXIT_SUCCESS;
}
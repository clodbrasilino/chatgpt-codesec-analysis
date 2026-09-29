#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *snake_to_camel(const char *snake)
{
    const unsigned char *source;
    size_t output_length = 0;
    size_t destination_index = 0;
    int capitalize_next = 1;
    char *camel;

    if (snake == NULL) {
        return NULL;
    }

    source = (const unsigned char *)snake;

    while (*source != '\0') {
        if (*source != (unsigned char)'_') {
            if (output_length == SIZE_MAX - 1) {
                return NULL;
            }
            ++output_length;
        }
        ++source;
    }

    camel = malloc(output_length + 1);
    if (camel == NULL) {
        return NULL;
    }

    source = (const unsigned char *)snake;

    while (*source != '\0') {
        if (*source == (unsigned char)'_') {
            capitalize_next = 1;
        } else if (capitalize_next) {
            camel[destination_index++] = (char)toupper(*source);
            capitalize_next = 0;
        } else {
            camel[destination_index++] = (char)*source;
        }
        ++source;
    }

    camel[destination_index] = '\0';
    return camel;
}

int main(int argc, char *argv[])
{
    char *camel;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <snake_case_string>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    camel = snake_to_camel(argv[1]);
    if (camel == NULL) {
        fputs("Failed to convert string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(camel) == EOF) {
        free(camel);
        return EXIT_FAILURE;
    }

    free(camel);
    return EXIT_SUCCESS;
}
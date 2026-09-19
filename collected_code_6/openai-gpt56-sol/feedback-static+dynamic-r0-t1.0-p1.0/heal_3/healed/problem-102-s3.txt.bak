#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *snake_to_camel(const char *snake)
{
    size_t length;
    size_t source_index;
    size_t destination_index = 0U;
    int capitalize_next = 1;
    char *camel;

    if (snake == NULL) {
        return NULL;
    }

    length = strlen(snake);
    if (length == SIZE_MAX) {
        return NULL;
    }

    camel = malloc(length + 1U);
    if (camel == NULL) {
        return NULL;
    }

    for (source_index = 0U; source_index < length; ++source_index) {
        const unsigned char character = (unsigned char)snake[source_index];

        if (character == (unsigned char)'_') {
            capitalize_next = 1;
        } else if (capitalize_next != 0) {
            camel[destination_index++] = (char)toupper(character);
            capitalize_next = 0;
        } else {
            camel[destination_index++] = (char)character;
        }
    }

    camel[destination_index] = '\0';
    return camel;
}

int main(int argc, const char *const argv[])
{
    char *camel;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <snake_case_string>\n", argv[0]);
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
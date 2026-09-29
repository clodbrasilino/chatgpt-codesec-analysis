#include <ctype.h>
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
        } else {
            camel[destination_index++] = capitalize_next
                ? (char)toupper(*source)
                : (char)*source;
            capitalize_next = 0;
        }
        ++source;
    }

    camel[destination_index] = '\0';
    return camel;
}

int main(int argc, char *argv[])
{
    char *camel;
    int result;

    if (argc == 2 && argv != NULL && argv[1] != NULL) {
        camel = snake_to_camel(argv[1]);
    } else {
        char input[4096];

        if (fgets(input, sizeof input, stdin) == NULL) {
            return EXIT_FAILURE;
        }

        input[strcspn(input, "\r\n")] = '\0';
        camel = snake_to_camel(input);
    }

    if (camel == NULL) {
        return EXIT_FAILURE;
    }

    result = puts(camel);
    free(camel);

    return result == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}
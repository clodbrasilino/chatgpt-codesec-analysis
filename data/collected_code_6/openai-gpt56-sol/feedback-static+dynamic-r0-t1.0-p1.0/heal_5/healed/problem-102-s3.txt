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
                ? (char)toupper((int)*source)
                : (char)*source;
            capitalize_next = 0;
        }
        ++source;
    }

    camel[destination_index] = '\0';
    return camel;
}

int main(int argc, char *const argv[])
{
    char *camel = NULL;

    if (argc == 2 && argv[1] != NULL) {
        camel = snake_to_camel(argv[1]);
    } else {
        char *input = NULL;
        size_t capacity = 0;
        size_t length = 0;
        int character;

        while ((character = getchar()) != EOF &&
               character != '\n' &&
               character != '\r') {
            if (length == SIZE_MAX - 1) {
                free(input);
                return EXIT_FAILURE;
            }

            if (length + 1 >= capacity) {
                char *resized;
                size_t new_capacity;

                if (capacity == 0) {
                    new_capacity = 128;
                } else {
                    if (capacity > SIZE_MAX / 2) {
                        free(input);
                        return EXIT_FAILURE;
                    }
                    new_capacity = capacity * 2;
                }

                if (new_capacity <= length) {
                    free(input);
                    return EXIT_FAILURE;
                }

                resized = realloc(input, new_capacity);
                if (resized == NULL) {
                    free(input);
                    return EXIT_FAILURE;
                }

                input = resized;
                capacity = new_capacity;
            }

            input[length++] = (char)(unsigned char)character;
        }

        if (ferror(stdin) || (character == EOF && length == 0)) {
            free(input);
            return EXIT_FAILURE;
        }

        if (input == NULL) {
            input = malloc(1);
            if (input == NULL) {
                return EXIT_FAILURE;
            }
        }

        input[length] = '\0';
        camel = snake_to_camel(input);
        free(input);
    }

    if (camel == NULL) {
        return EXIT_FAILURE;
    }

    if (puts(camel) == EOF) {
        free(camel);
        return EXIT_FAILURE;
    }

    free(camel);
    return EXIT_SUCCESS;
}
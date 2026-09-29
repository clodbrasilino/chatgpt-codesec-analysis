#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void remove_non_alphanumeric(char *string)
{
    unsigned char *read_ptr = (unsigned char *)string;
    char *write_ptr = string;

    while (*read_ptr != '\0') {
        if (isalnum(*read_ptr)) {
            *write_ptr++ = (char)*read_ptr;
        }
        ++read_ptr;
    }

    *write_ptr = '\0';
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        size_t required;
        size_t new_capacity;
        char *temporary;

        if (length > SIZE_MAX - 2) {
            free(input);
            return EXIT_FAILURE;
        }

        required = length + 2;

        if (required > capacity) {
            new_capacity = capacity == 0 ? 128 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
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
    remove_non_alphanumeric(input);

    if (puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static unsigned char add_characters(const unsigned char *string)
{
    unsigned int sum = 0U;

    while (*string != '\0') {
        sum = (sum + *string) % 256U;
        ++string;
    }

    return (unsigned char)sum;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length > SIZE_MAX - 2U) {
            free(input);
            return EXIT_FAILURE;
        }

        if (capacity < length + 2U) {
            size_t required = length + 2U;
            size_t new_capacity = capacity == 0U ? 128U : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2U) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2U;
            }

            unsigned char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1U);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    unsigned char result = add_characters(input);
    free(input);

    if (printf("%c\n", (int)result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned char add_characters(const unsigned char *string, size_t length)
{
    unsigned int sum = 0U;

    for (size_t i = 0U; i < length; ++i) {
        sum = (sum + string[i]) & 0xFFU;
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
        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2U;
            }

            unsigned char *temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    unsigned char result = add_characters(input, length);
    free(input);

    if (printf("%c\n", (int)result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
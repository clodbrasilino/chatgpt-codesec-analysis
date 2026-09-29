#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint8_t add_characters(const unsigned char *string, size_t length)
{
    uint8_t sum = 0;

    for (size_t i = 0; i < length; ++i) {
        sum = (uint8_t)(sum + string[i]);
    }

    return sum;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 4096 };

    unsigned char *input = malloc(MAX_INPUT_LENGTH);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0;
    int character;

    for (;;) {
        character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length == MAX_INPUT_LENGTH) {
            free(input);
            return EXIT_FAILURE;
        }

        input[length++] = (unsigned char)character;
    }

    uint8_t result = add_characters(input, length);
    free(input);

    if (putchar((int)result) == EOF || putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
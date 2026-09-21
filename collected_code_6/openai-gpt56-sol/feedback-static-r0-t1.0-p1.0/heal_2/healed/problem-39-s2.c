#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_CAPACITY 4096U

static bool can_rearrange_without_adjacent_duplicates(
    const unsigned char *string,
    size_t length)
{
    size_t frequencies[256] = {0};
    size_t maximum = 0;

    if (string == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t frequency = ++frequencies[string[i]];

        if (frequency > maximum) {
            maximum = frequency;
        }
    }

    return maximum <= (length / 2U) + (length % 2U);
}

int main(void)
{
    unsigned char *input = malloc(INPUT_CAPACITY);

    if (input == NULL) {
        return 1;
    }

    size_t length = 0;
    int character = 0;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length >= INPUT_CAPACITY - 1U) {
            do {
                character = fgetc(stdin);
            } while (character != EOF && character != '\n');

            free(input);
            return 1;
        }

        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin) || (character == EOF && length == 0U)) {
        free(input);
        return 1;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    input[length] = '\0';

    puts(can_rearrange_without_adjacent_duplicates(input, length)
             ? "true"
             : "false");

    free(input);
    return 0;
}
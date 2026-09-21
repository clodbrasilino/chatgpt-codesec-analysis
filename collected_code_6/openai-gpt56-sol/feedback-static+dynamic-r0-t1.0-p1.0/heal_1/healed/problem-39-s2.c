#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define INPUT_CAPACITY 4096U

static bool can_rearrange_without_adjacent_duplicates(
    const char *string,
    size_t length)
{
    size_t frequencies[256] = {0};
    size_t maximum = 0;

    if (string == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)string[i];

        ++frequencies[character];
        if (frequencies[character] > maximum) {
            maximum = frequencies[character];
        }
    }

    return maximum <= (length / 2U) + (length % 2U);
}

int main(void)
{
    char input[INPUT_CAPACITY];
    size_t length = 0;
    int character;
    bool too_long = false;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length + 1U < sizeof input) {
            input[length++] = (char)character;
        } else {
            too_long = true;
        }
    }

    if (ferror(stdin) || too_long || (character == EOF && length == 0U)) {
        return 1;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    input[length] = '\0';

    puts(can_rearrange_without_adjacent_duplicates(input, length)
             ? "true"
             : "false");

    return 0;
}
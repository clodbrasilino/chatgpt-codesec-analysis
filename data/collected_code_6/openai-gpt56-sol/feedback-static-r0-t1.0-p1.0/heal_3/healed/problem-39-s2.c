#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

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

    return maximum <= (length + 1U) / 2U;
}

int main(void)
{
    unsigned char input[INPUT_CAPACITY];

    if (fgets((char *)input, sizeof input, stdin) == NULL) {
        return 1;
    }

    size_t length = 0;

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else if (length == sizeof input - 1U) {
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            while ((character = fgetc(stdin)) != '\n' && character != EOF) {
            }
            return 1;
        }

        if (character == EOF && ferror(stdin)) {
            return 1;
        }
    }

    if (length > 0U && input[length - 1U] == '\r') {
        input[--length] = '\0';
    }

    puts(can_rearrange_without_adjacent_duplicates(input, length)
             ? "true"
             : "false");

    return 0;
}
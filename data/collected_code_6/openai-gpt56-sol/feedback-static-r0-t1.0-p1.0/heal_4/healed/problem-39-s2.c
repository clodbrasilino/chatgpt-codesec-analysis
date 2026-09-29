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

    return maximum <= length / 2U + length % 2U;
}

static bool read_line(unsigned char *buffer, size_t capacity, size_t *length)
{
    if (buffer == NULL || length == NULL || capacity < 2U) {
        return false;
    }

    if (fgets((char *)buffer, (int)capacity, stdin) == NULL) {
        return false;
    }

    size_t used = 0;

    while (used < capacity && buffer[used] != '\0' && buffer[used] != '\n') {
        ++used;
    }

    if (used < capacity && buffer[used] == '\n') {
        buffer[used] = '\0';
    } else {
        int character = getchar();

        if (character != '\n' && character != EOF) {
            do {
                character = getchar();
            } while (character != '\n' && character != EOF);

            return false;
        }

        if (character == EOF && ferror(stdin)) {
            return false;
        }
    }

    if (used > 0U && buffer[used - 1U] == '\r') {
        --used;
        buffer[used] = '\0';
    }

    *length = used;
    return true;
}

int main(void)
{
    unsigned char input[INPUT_CAPACITY];
    size_t length = 0;

    if (!read_line(input, sizeof input, &length)) {
        return 1;
    }

    puts(can_rearrange_without_adjacent_duplicates(input, length)
             ? "true"
             : "false");

    return 0;
}
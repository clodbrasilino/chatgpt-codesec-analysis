#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define INPUT_CAPACITY 1024U

static bool has_two_alternating_characters(const char *str, size_t length)
{
    if (str == NULL || length < 2U || str[0] == str[1]) {
        return false;
    }

    for (size_t i = 2U; i < length; ++i) {
        if (str[i] != str[i % 2U]) {
            return false;
        }
    }

    return true;
}

static bool read_line(char *buffer, size_t capacity, size_t *length)
{
    if (buffer == NULL || length == NULL || capacity < 2U) {
        return false;
    }

    size_t index = 0U;
    int character = 0;

    while (index + 1U < capacity) {
        character = fgetc(stdin);

        if (character == '\n') {
            buffer[index] = '\0';
            *length = index;
            return true;
        }

        if (character == EOF) {
            if (ferror(stdin) || index == 0U) {
                return false;
            }

            buffer[index] = '\0';
            *length = index;
            return true;
        }

        buffer[index++] = (char)character;
    }

    buffer[index] = '\0';
    character = fgetc(stdin);

    if (character == '\n' || (character == EOF && !ferror(stdin))) {
        *length = index;
        return true;
    }

    while (character != '\n' && character != EOF) {
        character = fgetc(stdin);
    }

    return false;
}

int main(void)
{
    char input[INPUT_CAPACITY + 1U];
    size_t length = 0U;

    if (!read_line(input, sizeof input, &length)) {
        return 1;
    }

    puts(has_two_alternating_characters(input, length) ? "Yes" : "No");
    return 0;
}
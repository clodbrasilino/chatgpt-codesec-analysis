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

static bool discard_remaining_input(void)
{
    int character;

    do {
        character = fgetc(stdin);
    } while (character != '\n' && character != EOF);

    return character == '\n' || !ferror(stdin);
}

static bool read_line(char *buffer, size_t capacity, size_t *length)
{
    if (buffer == NULL || length == NULL || capacity < 2U) {
        return false;
    }

    *length = 0U;

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
            buffer[index] = '\0';

            if (ferror(stdin) || index == 0U) {
                return false;
            }

            *length = index;
            return true;
        }

        buffer[index++] = (char)character;
    }

    buffer[index] = '\0';

    character = fgetc(stdin);

    if (character == '\n') {
        *length = index;
        return true;
    }

    if (character == EOF) {
        if (ferror(stdin)) {
            return false;
        }

        *length = index;
        return true;
    }

    (void)discard_remaining_input();
    return false;
}

int main(void)
{
    char input[INPUT_CAPACITY + 1U];
    size_t length = 0U;

    if (!read_line(input, sizeof input, &length)) {
        return 1;
    }

    if (puts(has_two_alternating_characters(input, length) ? "Yes" : "No") == EOF) {
        return 1;
    }

    return 0;
}
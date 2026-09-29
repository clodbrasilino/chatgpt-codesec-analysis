#include <stdbool.h>
#include <stdio.h>

#define INPUT_CAPACITY 1024U

static bool has_two_alternating_characters(const char *str, size_t length)
{
    if (str == NULL || length < 2U || str[0] == str[1]) {
        return false;
    }

    for (size_t i = 2U; i < length; ++i) {
        if (str[i] != ((i % 2U == 0U) ? str[0] : str[1])) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char input[INPUT_CAPACITY];
    size_t length = 0U;
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length >= sizeof input) {
            do {
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            return 1;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        return 1;
    }

    if (character == EOF && length == 0U) {
        return 1;
    }

    puts(has_two_alternating_characters(input, length) ? "Yes" : "No");
    return 0;
}
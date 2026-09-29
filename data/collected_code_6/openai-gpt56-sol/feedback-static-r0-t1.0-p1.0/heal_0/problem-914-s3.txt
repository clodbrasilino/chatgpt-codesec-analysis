#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool has_two_alternating_characters(const char *str)
{
    size_t length;
    char first;
    char second;

    if (str == NULL) {
        return false;
    }

    length = strlen(str);
    if (length < 2U) {
        return false;
    }

    first = str[0];
    second = str[1];

    if (first == second) {
        return false;
    }

    for (size_t i = 2U; i < length; ++i) {
        const char expected = (i % 2U == 0U) ? first : second;

        if (str[i] != expected) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    size_t length = strlen(input);

    if (length > 0U && input[length - 1U] == '\n') {
        input[--length] = '\0';
    } else if (length == sizeof input - 1U) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (character != '\n') {
            return 1;
        }
    }

    puts(has_two_alternating_characters(input) ? "Yes" : "No");
    return 0;
}
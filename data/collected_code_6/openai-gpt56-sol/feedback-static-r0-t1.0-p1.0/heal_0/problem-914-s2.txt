#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool has_two_alternating_characters(const char *string)
{
    if (string == NULL || string[0] == '\0' || string[1] == '\0') {
        return false;
    }

    const char first = string[0];
    const char second = string[1];

    if (first == second) {
        return false;
    }

    for (size_t i = 2U; string[i] != '\0'; ++i) {
        const char expected = (i % 2U == 0U) ? first : second;

        if (string[i] != expected) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            return 1;
        }
        return 0;
    }

    size_t length = 0U;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] == '\0' && !feof(stdin)) {
        int character;
        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (ferror(stdin) != 0) {
            return 1;
        }

        return 1;
    }

    if (printf("%s\n",
               has_two_alternating_characters(input) ? "true" : "false") < 0) {
        return 1;
    }

    return 0;
}
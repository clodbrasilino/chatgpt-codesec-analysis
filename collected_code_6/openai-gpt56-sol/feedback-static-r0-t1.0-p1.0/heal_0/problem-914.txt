#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static bool has_two_alternating_characters(const char *string)
{
    size_t length;

    if (string == NULL) {
        return false;
    }

    length = strlen(string);

    if (length < 2U || string[0] == string[1]) {
        return false;
    }

    for (size_t i = 2U; i < length; ++i) {
        if (string[i] != string[i % 2U]) {
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
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        if (ch != '\n') {
            return 1;
        }

        return 1;
    }

    puts(has_two_alternating_characters(input) ? "Yes" : "No");
    return 0;
}
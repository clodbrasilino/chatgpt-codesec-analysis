#include <stdio.h>
#include <stdbool.h>

enum { INPUT_CAPACITY = 1024 };

static bool has_two_alternating_characters(const char *string, size_t length)
{
    if (string == NULL || length < 2U || string[0] == string[1]) {
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
    char input[INPUT_CAPACITY];
    size_t length = 0U;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1U >= sizeof input) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            return 1;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        return 1;
    }

    input[length] = '\0';

    puts(has_two_alternating_characters(input, length) ? "Yes" : "No");
    return 0;
}
#include <stdbool.h>
#include <stdio.h>

enum { INPUT_CAPACITY = 1024 };

static bool is_binary_string(const char *str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    for (; *str != '\0'; ++str) {
        if (*str != '0' && *str != '1') {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char input[INPUT_CAPACITY];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = 0U;

    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stdin)) {
            return 1;
        }

        fputs("Not a binary string\n", stdout);
        return 0;
    }

    if (is_binary_string(input)) {
        fputs("Binary string\n", stdout);
    } else {
        fputs("Not a binary string\n", stdout);
    }

    return 0;
}
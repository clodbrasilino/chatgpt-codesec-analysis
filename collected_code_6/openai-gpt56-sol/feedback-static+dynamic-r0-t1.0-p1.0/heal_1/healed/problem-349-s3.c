#include <stdbool.h>
#include <stdio.h>

enum { INPUT_CAPACITY = 1024 };

static bool is_binary_string(const char *str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    while (*str != '\0') {
        if (*str != '0' && *str != '1') {
            return false;
        }
        ++str;
    }

    return true;
}

int main(void)
{
    char input[INPUT_CAPACITY];
    size_t length = 0U;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1U >= sizeof input) {
            while (ch != '\n' && ch != EOF) {
                ch = getchar();
            }

            fputs("Not a binary string\n", stdout);
            return 0;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        return 1;
    }

    input[length] = '\0';

    if (is_binary_string(input)) {
        fputs("Binary string\n", stdout);
    } else {
        fputs("Not a binary string\n", stdout);
    }

    return 0;
}
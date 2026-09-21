#include <stdbool.h>
#include <stdio.h>

enum { INPUT_SIZE = 1024 };

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
    char input[INPUT_SIZE];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    size_t length = 0;

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        if (length == sizeof input - 1U || ch != '\n') {
            fputs("Not a binary string\n", stdout);
            return 0;
        }
    }

    fputs(is_binary_string(input) ? "Binary string\n"
                                  : "Not a binary string\n",
          stdout);

    return 0;
}
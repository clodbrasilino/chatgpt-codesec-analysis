#include <stdio.h>

static int is_binary_string(const char *str)
{
    if (str == NULL || *str == '\0') {
        return 0;
    }

    while (*str != '\0') {
        if (*str != '0' && *str != '1') {
            return 0;
        }
        ++str;
    }

    return 1;
}

int main(void)
{
    char input[1024];
    char *newline;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    newline = strchr(input, '\n');

    if (newline != NULL) {
        if (newline > input && newline[-1] == '\r') {
            --newline;
        }
        *newline = '\0';
    } else if (!feof(stdin)) {
        int character;

        do {
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        return 1;
    }

    puts(is_binary_string(input) ? "Binary string" : "Not a binary string");
    return 0;
}
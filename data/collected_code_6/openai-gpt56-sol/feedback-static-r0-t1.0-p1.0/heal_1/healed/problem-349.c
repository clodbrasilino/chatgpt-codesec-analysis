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
    size_t length = 0;
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1 >= sizeof input) {
            while ((character = fgetc(stdin)) != '\n' && character != EOF) {
            }
            return 1;
        }

        input[length++] = (char)character;
    }

    if (length > 0 && input[length - 1] == '\r') {
        --length;
    }

    input[length] = '\0';

    if (character == EOF && ferror(stdin)) {
        return 1;
    }

    puts(is_binary_string(input) ? "Binary string" : "Not a binary string");
    return 0;
}
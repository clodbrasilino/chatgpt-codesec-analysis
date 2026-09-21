#include <stdio.h>
#include <string.h>

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

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    size_t length = strcspn(input, "\r\n");

    if (input[length] == '\0' && length == sizeof input - 1) {
        int character;

        while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        }

        return 1;
    }

    input[length] = '\0';

    puts(is_binary_string(input) ? "Binary string" : "Not a binary string");
    return 0;
}
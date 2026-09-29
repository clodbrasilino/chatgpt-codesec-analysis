#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool ends_with_number(const char *str, size_t length)
{
    if (str == NULL || length == 0) {
        return false;
    }

    return isdigit((unsigned char)str[length - 1]) != 0;
}

int main(void)
{
    char input[1024];
    size_t length = 0;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length < sizeof input - 1) {
            input[length++] = (char)ch;
        }
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    input[length] = '\0';

    printf("%s\n", ends_with_number(input, length) ? "true" : "false");
    return 0;
}
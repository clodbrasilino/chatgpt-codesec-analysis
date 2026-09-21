#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

static bool ends_with_number(const char *string, size_t length)
{
    return string != NULL &&
           length > 0U &&
           isdigit((unsigned char)string[length - 1U]) != 0;
}

int main(void)
{
    char input[1024];
    size_t length = 0U;
    bool truncated = false;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) != 0 ? 1 : 0;
    }

    while (input[length] != '\0' && input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (input[length] == '\0' && length == sizeof input - 1U) {
        int character;

        truncated = true;
        while ((character = getchar()) != '\n' && character != EOF) {
            if (character == '\r') {
                int next = getchar();

                if (next != '\n' && next != EOF) {
                    ungetc(next, stdin);
                }
                break;
            }
        }

        if (ferror(stdin) != 0) {
            return 1;
        }
    }

    if (truncated) {
        fputs("Input is too long.\n", stderr);
        return 1;
    }

    if (ends_with_number(input, length)) {
        puts("The string ends with a number.");
    } else {
        puts("The string does not end with a number.");
    }

    return 0;
}
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
    int character;

    while ((character = getchar()) != EOF && character != '\n') {
        if (character == '\r') {
            int next = getchar();

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            }
            break;
        }

        if (length < sizeof input) {
            input[length++] = (char)character;
        }
    }

    if (ferror(stdin) != 0) {
        return 1;
    }

    if (character == EOF && length == 0U) {
        return 0;
    }

    if (ends_with_number(input, length)) {
        puts("The string ends with a number.");
    } else {
        puts("The string does not end with a number.");
    }

    return 0;
}
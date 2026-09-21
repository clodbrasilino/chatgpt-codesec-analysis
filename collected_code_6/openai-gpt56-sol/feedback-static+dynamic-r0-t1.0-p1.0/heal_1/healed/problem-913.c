#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

static bool ends_with_number(const char *str, size_t length)
{
    return str != NULL &&
           length > 0U &&
           isdigit((unsigned char)str[length - 1U]) != 0;
}

int main(void)
{
    char input[1024];
    size_t length = 0U;
    int ch;

    while (length < sizeof input && (ch = getchar()) != EOF &&
           ch != '\n' && ch != '\r') {
        input[length++] = (char)ch;
    }

    if (ch == '\r') {
        int next = getchar();

        if (next != '\n' && next != EOF) {
            ungetc(next, stdin);
        }
    } else if (length == sizeof input && ch != '\n' && ch != EOF) {
        while ((ch = getchar()) != EOF && ch != '\n') {
        }
    }

    if (ferror(stdin) != 0) {
        return 1;
    }

    if (length == 0U && ch == EOF) {
        return 0;
    }

    if (printf("%s\n", ends_with_number(input, length) ? "true" : "false") < 0) {
        return 1;
    }

    return 0;
}
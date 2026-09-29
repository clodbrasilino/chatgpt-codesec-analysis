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
    int current;
    int last = EOF;
    bool has_input = false;

    while ((current = getchar()) != EOF) {
        if (current == '\n') {
            break;
        }

        if (current == '\r') {
            int next = getchar();

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            }
            break;
        }

        last = current;
        has_input = true;
    }

    if (ferror(stdin) != 0) {
        return 1;
    }

    {
        const char value[1] = {(char)last};

        if (printf("%s\n",
                   has_input && ends_with_number(value, sizeof value)
                       ? "true"
                       : "false") < 0) {
            return 1;
        }
    }

    return 0;
}
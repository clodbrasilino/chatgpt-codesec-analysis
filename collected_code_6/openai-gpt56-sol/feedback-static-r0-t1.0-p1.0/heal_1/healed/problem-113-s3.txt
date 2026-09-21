#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

static bool is_integer(const char *str)
{
    const unsigned char *p = (const unsigned char *)str;

    if (p == NULL || *p == '\0') {
        return false;
    }

    if (*p == '+' || *p == '-') {
        ++p;
    }

    if (*p == '\0') {
        return false;
    }

    while (*p != '\0') {
        if (!isdigit(*p)) {
            return false;
        }
        ++p;
    }

    return true;
}

int main(void)
{
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = 0;

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);
            return 1;
        }

        if (ch == EOF && ferror(stdin)) {
            return 1;
        }
    }

    return printf("%s\n", is_integer(input) ? "true" : "false") < 0 ? 1 : 0;
}
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool is_integer(const char *str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    const unsigned char *p = (const unsigned char *)str;

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

    char *newline = strchr(input, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            return 1;
        }

        if (ch == EOF && ferror(stdin)) {
            return 1;
        }
    }

    if (printf("%s\n", is_integer(input) ? "true" : "false") < 0) {
        return 1;
    }

    return 0;
}
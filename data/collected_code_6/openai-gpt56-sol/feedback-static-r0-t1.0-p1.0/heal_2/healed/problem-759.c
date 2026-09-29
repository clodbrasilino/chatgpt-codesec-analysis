#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

static bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p = (const unsigned char *)text;

    if (p == NULL || *p == '\0') {
        return false;
    }

    if (*p == '+' || *p == '-') {
        ++p;
    }

    if (!isdigit(*p)) {
        return false;
    }

    do {
        ++p;
    } while (isdigit(*p));

    if (*p++ != '.') {
        return false;
    }

    if (!isdigit(*p++)) {
        return false;
    }

    if (!isdigit(*p++)) {
        return false;
    }

    return *p == '\0';
}

int main(void)
{
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;
        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ferror(stdin)) {
            return 1;
        }

        puts("Invalid");
        return 0;
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[length - 1] = '\0';
    }

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");
    return 0;
}
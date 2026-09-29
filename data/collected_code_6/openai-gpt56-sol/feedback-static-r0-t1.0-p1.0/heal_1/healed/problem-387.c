#include <ctype.h>
#include <stdio.h>

enum { INPUT_SIZE = 1024 };

static int is_hexadecimal(const char *text, size_t length)
{
    size_t index = 0;

    if (text == NULL || length == 0) {
        return 0;
    }

    if (length >= 2 &&
        text[0] == '0' &&
        (text[1] == 'x' || text[1] == 'X')) {
        index = 2;
    }

    if (index == length) {
        return 0;
    }

    for (; index < length; ++index) {
        if (!isxdigit((unsigned char)text[index])) {
            return 0;
        }
    }

    return 1;
}

static int is_hex_even(const char *text, size_t length)
{
    unsigned char last_digit = (unsigned char)text[length - 1];

    if (last_digit >= '0' && last_digit <= '9') {
        return ((last_digit - '0') % 2U) == 0U;
    }

    last_digit = (unsigned char)tolower(last_digit);
    return ((last_digit - 'a' + 10U) % 2U) == 0U;
}

int main(void)
{
    char input[INPUT_SIZE];
    size_t length = 0;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1U >= sizeof input) {
            do {
                character = getchar();
            } while (character != '\n' && character != EOF);

            fputs("Input too long\n", stderr);
            return 1;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        fputs("Input error\n", stderr);
        return 1;
    }

    input[length] = '\0';

    if (!is_hexadecimal(input, length)) {
        fputs("Invalid hexadecimal number\n", stderr);
        return 1;
    }

    puts(is_hex_even(input, length) ? "Even" : "Odd");
    return 0;
}
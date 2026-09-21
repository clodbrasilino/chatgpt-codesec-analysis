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
    unsigned char last_digit;

    if (text == NULL || length == 0) {
        return 0;
    }

    last_digit = (unsigned char)text[length - 1];

    if (last_digit >= (unsigned char)'0' &&
        last_digit <= (unsigned char)'9') {
        return ((last_digit - (unsigned char)'0') & 1U) == 0U;
    }

    if (last_digit >= (unsigned char)'A' &&
        last_digit <= (unsigned char)'F') {
        return ((last_digit - (unsigned char)'A' + 10U) & 1U) == 0U;
    }

    if (last_digit >= (unsigned char)'a' &&
        last_digit <= (unsigned char)'f') {
        return ((last_digit - (unsigned char)'a' + 10U) & 1U) == 0U;
    }

    return 0;
}

int main(void)
{
    char input[INPUT_SIZE];
    size_t length = 0;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length >= sizeof input - 1U) {
            while (character != '\n' && character != EOF) {
                character = getchar();
            }

            if (character == EOF && ferror(stdin)) {
                fputs("Input error\n", stderr);
            } else {
                fputs("Input too long\n", stderr);
            }

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
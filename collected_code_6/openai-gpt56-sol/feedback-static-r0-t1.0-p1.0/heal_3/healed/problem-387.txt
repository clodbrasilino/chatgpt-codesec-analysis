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
    unsigned char digit;

    if (text == NULL || length == 0) {
        return 0;
    }

    digit = (unsigned char)text[length - 1];

    if (digit >= (unsigned char)'0' && digit <= (unsigned char)'9') {
        return ((digit - (unsigned char)'0') & 1U) == 0U;
    }

    if (digit >= (unsigned char)'A' && digit <= (unsigned char)'F') {
        return ((digit - (unsigned char)'A' + 10U) & 1U) == 0U;
    }

    if (digit >= (unsigned char)'a' && digit <= (unsigned char)'f') {
        return ((digit - (unsigned char)'a' + 10U) & 1U) == 0U;
    }

    return 0;
}

static int discard_line(void)
{
    int character;

    do {
        character = getchar();
    } while (character != '\n' && character != EOF);

    return character;
}

int main(void)
{
    char input[INPUT_SIZE];
    size_t length;
    int character;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
        } else {
            fputs("No input\n", stderr);
        }
        return 1;
    }

    for (length = 0; length < sizeof input && input[length] != '\0'; ++length) {
        if (input[length] == '\n') {
            input[length] = '\0';
            break;
        }
    }

    if (length == sizeof input) {
        fputs("Input error\n", stderr);
        return 1;
    }

    if (input[length] != '\0') {
        fputs("Input error\n", stderr);
        return 1;
    }

    if (length == sizeof input - 1U) {
        character = discard_line();

        if (character == EOF && ferror(stdin)) {
            fputs("Input error\n", stderr);
        } else if (character != '\n') {
            fputs("Input too long\n", stderr);
        } else {
            fputs("Input too long\n", stderr);
        }

        return 1;
    }

    if (!is_hexadecimal(input, length)) {
        fputs("Invalid hexadecimal number\n", stderr);
        return 1;
    }

    puts(is_hex_even(input, length) ? "Even" : "Odd");
    return 0;
}
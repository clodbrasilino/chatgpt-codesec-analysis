#include <ctype.h>
#include <stdio.h>

static int is_hex_even(const char *hex, size_t length, int *is_even)
{
    size_t begin;
    size_t end;
    unsigned char last;

    if (hex == NULL || is_even == NULL) {
        return 0;
    }

    begin = 0U;
    end = length;

    while (begin < end && isspace((unsigned char)hex[begin])) {
        ++begin;
    }

    while (begin < end && isspace((unsigned char)hex[end - 1U])) {
        --end;
    }

    if (end >= begin + 2U &&
        hex[begin] == '0' &&
        (hex[begin + 1U] == 'x' || hex[begin + 1U] == 'X')) {
        begin += 2U;
    }

    if (begin >= end) {
        return 0;
    }

    for (size_t i = begin; i < end; ++i) {
        if (!isxdigit((unsigned char)hex[i])) {
            return 0;
        }
    }

    last = (unsigned char)hex[end - 1U];
    *is_even = last == '0' || last == '2' || last == '4' ||
               last == '6' || last == '8' || last == 'a' ||
               last == 'c' || last == 'e' || last == 'A' ||
               last == 'C' || last == 'E';

    return 1;
}

int main(void)
{
    char input[4096];
    size_t length = 0U;
    int is_even;
    int ch;
    int overflow = 0;

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length < sizeof(input)) {
            input[length++] = (char)ch;
        } else {
            overflow = 1;
        }
    }

    if (ferror(stdin)) {
        fputs("Input error\n", stderr);
        return 1;
    }

    if (overflow || !is_hex_even(input, length, &is_even)) {
        fputs("Invalid hexadecimal number\n", stderr);
        return 1;
    }

    puts(is_even ? "Even" : "Odd");
    return 0;
}
#include <ctype.h>
#include <stdio.h>

static int is_hex_even(const char *hex, size_t length, int *is_even)
{
    size_t begin = 0U;
    size_t end = length;
    unsigned char last;

    if (hex == NULL || is_even == NULL) {
        return 0;
    }

    while (begin < end && isspace((unsigned char)hex[begin])) {
        ++begin;
    }

    while (end > begin && isspace((unsigned char)hex[end - 1U])) {
        --end;
    }

    if (end - begin >= 2U &&
        hex[begin] == '0' &&
        (hex[begin + 1U] == 'x' || hex[begin + 1U] == 'X')) {
        begin += 2U;
    }

    if (begin == end) {
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
    int is_even;
    int ch;
    int last = EOF;
    int saw_input = 0;
    int too_long = 0;
    enum { MAX_INPUT_LENGTH = 1023 };
    char input[MAX_INPUT_LENGTH];
    size_t length = 0U;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        saw_input = 1;
        last = ch;

        if (length < sizeof input) {
            input[length++] = (char)ch;
        } else {
            too_long = 1;
        }
    }

    if (ch == EOF && ferror(stdin)) {
        fputs("Input error\n", stderr);
        return 1;
    }

    if (!saw_input && ch == EOF) {
        fputs("Input error\n", stderr);
        return 1;
    }

    if (too_long) {
        fputs("Input too long\n", stderr);
        return 1;
    }

    if (last == '\r') {
        --length;
    }

    if (!is_hex_even(input, length, &is_even)) {
        fputs("Invalid hexadecimal number\n", stderr);
        return 1;
    }

    puts(is_even ? "Even" : "Odd");
    return 0;
}
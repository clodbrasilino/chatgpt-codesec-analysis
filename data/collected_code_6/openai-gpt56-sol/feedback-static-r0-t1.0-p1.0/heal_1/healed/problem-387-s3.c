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
    unsigned char last_hex_digit = 0U;
    int have_digit = 0;
    int invalid = 0;
    int prefix_possible = 1;
    int prefix_seen = 0;
    int trailing_space = 0;

    while ((ch = getchar()) != EOF && ch != '\n') {
        unsigned char c = (unsigned char)ch;

        if (!have_digit && !prefix_seen && isspace(c)) {
            continue;
        }

        if (prefix_possible && c == '0') {
            prefix_possible = 0;
            last_hex_digit = c;
            have_digit = 1;
            continue;
        }

        if (have_digit && !prefix_seen && last_hex_digit == '0' &&
            (c == 'x' || c == 'X')) {
            prefix_seen = 1;
            have_digit = 0;
            trailing_space = 0;
            continue;
        }

        prefix_possible = 0;

        if (isspace(c)) {
            if (have_digit) {
                trailing_space = 1;
            }
            continue;
        }

        if (trailing_space || !isxdigit(c)) {
            invalid = 1;
            continue;
        }

        last_hex_digit = c;
        have_digit = 1;
    }

    if (ferror(stdin)) {
        fputs("Input error\n", stderr);
        return 1;
    }

    if (invalid || !have_digit ||
        !is_hex_even((const char *)&last_hex_digit, 1U, &is_even)) {
        fputs("Invalid hexadecimal number\n", stderr);
        return 1;
    }

    puts(is_even ? "Even" : "Odd");
    return 0;
}
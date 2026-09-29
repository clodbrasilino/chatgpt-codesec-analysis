#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_CAPACITY 4096U

static int is_hex_even(const char *hex, size_t length, int *is_even)
{
    size_t begin = 0U;
    size_t end = length;
    unsigned char digit;

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

    digit = (unsigned char)hex[end - 1U];

    if (digit >= (unsigned char)'0' && digit <= (unsigned char)'9') {
        digit = (unsigned char)(digit - (unsigned char)'0');
    } else {
        digit = (unsigned char)(
            (unsigned char)tolower(digit) - (unsigned char)'a' + 10U
        );
    }

    *is_even = (digit & 1U) == 0U;
    return 1;
}

int main(void)
{
    char *input = malloc(INPUT_CAPACITY + 1U);
    size_t length = 0U;
    int is_even = 0;

    if (input == NULL) {
        fputs("Memory allocation error\n", stderr);
        return 1;
    }

    if (fgets(input, (int)(INPUT_CAPACITY + 1U), stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Invalid hexadecimal number\n", stderr);
        }
        free(input);
        return 1;
    }

    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            if (ferror(stdin)) {
                fputs("Input error\n", stderr);
            } else {
                fputs("Invalid hexadecimal number\n", stderr);
            }

            free(input);
            return 1;
        }

        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
            free(input);
            return 1;
        }
    }

    if (!is_hex_even(input, length, &is_even)) {
        fputs("Invalid hexadecimal number\n", stderr);
        free(input);
        return 1;
    }

    puts(is_even ? "Even" : "Odd");
    free(input);
    return 0;
}
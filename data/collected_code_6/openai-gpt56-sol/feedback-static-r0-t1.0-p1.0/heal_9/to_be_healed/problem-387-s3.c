#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_CAPACITY 4096U

static int is_hex_even(const char *hex, size_t length, int *is_even)
{
    size_t begin = 0U;
    size_t end = length;
    unsigned char last;

    if (hex == NULL || is_even == NULL) {
        return 0;
    }

    while (begin < end && isspace((unsigned char)hex[begin]) != 0) {
        ++begin;
    }

    while (begin < end && isspace((unsigned char)hex[end - 1U]) != 0) {
        --end;
    }

    if (begin == end) {
        return 0;
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
        if (isxdigit((unsigned char)hex[i]) == 0) {
            return 0;
        }
    }

    last = (unsigned char)hex[end - 1U];
    *is_even = last == (unsigned char)'0' ||
               last == (unsigned char)'2' ||
               last == (unsigned char)'4' ||
               last == (unsigned char)'6' ||
               last == (unsigned char)'8' ||
               last == (unsigned char)'A' ||
               last == (unsigned char)'C' ||
               last == (unsigned char)'E' ||
               last == (unsigned char)'a' ||
               last == (unsigned char)'c' ||
               last == (unsigned char)'e';

    return 1;
}

static int discard_line(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    for (;;) {
        if (fgets(buffer, (int)sizeof buffer, stdin) == NULL) {
            return ferror(stdin) == 0;
        }

        if (strchr(buffer, '\n') != NULL) {
            return 1;
        }
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY + 2U];
    size_t length;
    int is_even;

    if (fgets(input, (int)sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Invalid hexadecimal number\n", stderr);
        }
        return EXIT_FAILURE;
    }

    length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > INPUT_CAPACITY) {
        if (!discard_line()) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Invalid hexadecimal number\n", stderr);
        }
        return EXIT_FAILURE;
    } else if (ferror(stdin) != 0) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    is_even = 0;
    if (!is_hex_even(input, length, &is_even)) {
        fputs("Invalid hexadecimal number\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_even ? "Even" : "Odd");
    return EXIT_SUCCESS;
}
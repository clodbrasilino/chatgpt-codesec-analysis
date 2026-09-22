#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_CAPACITY 4096U

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

    while (begin < end && isspace((unsigned char)hex[begin]) != 0) {
        ++begin;
    }

    while (begin < end && isspace((unsigned char)hex[end - 1U]) != 0) {
        --end;
    }

    if (begin == end) {
        return 0;
    }

    if ((end - begin) >= 2U &&
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

    if (last >= (unsigned char)'0' && last <= (unsigned char)'9') {
        *is_even = (((unsigned int)(last - (unsigned char)'0') & 1U) == 0U);
    } else {
        *is_even = (last == (unsigned char)'A' ||
                    last == (unsigned char)'C' ||
                    last == (unsigned char)'E' ||
                    last == (unsigned char)'a' ||
                    last == (unsigned char)'c' ||
                    last == (unsigned char)'e');
    }

    return 1;
}

int main(void)
{
    char *input;
    size_t length;
    int is_even;
    int ch;

    input = malloc((size_t)INPUT_CAPACITY + 1U);
    if (input == NULL) {
        fputs("Memory allocation error\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)(INPUT_CAPACITY + 1U), stdin) == NULL) {
        if (ferror(stdin) != 0) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Invalid hexadecimal number\n", stderr);
        }
        free(input);
        return EXIT_FAILURE;
    }

    length = 0U;
    while (length < INPUT_CAPACITY &&
           input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < INPUT_CAPACITY && input[length] == '\n') {
        input[length] = '\0';
    } else {
        ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            if (ferror(stdin) != 0) {
                fputs("Input error\n", stderr);
            } else {
                fputs("Invalid hexadecimal number\n", stderr);
            }

            free(input);
            return EXIT_FAILURE;
        }

        if (ferror(stdin) != 0) {
            fputs("Input error\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }
    }

    is_even = 0;
    if (is_hex_even(input, length, &is_even) == 0) {
        fputs("Invalid hexadecimal number\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_even != 0 ? "Even" : "Odd");

    free(input);
    return EXIT_SUCCESS;
}
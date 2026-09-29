#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_CAPACITY 1024U

static int is_hex_digit(unsigned char character)
{
    return (character >= (unsigned char)'0' &&
            character <= (unsigned char)'9') ||
           (character >= (unsigned char)'a' &&
            character <= (unsigned char)'f') ||
           (character >= (unsigned char)'A' &&
            character <= (unsigned char)'F');
}

static int read_line(char *buffer, size_t capacity)
{
    size_t length;

    if (buffer == NULL || capacity < 2U || capacity > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        buffer[0] = '\0';
        return ferror(stdin) ? -1 : 1;
    }

    for (length = 0U; length < capacity && buffer[length] != '\0'; ++length) {
        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            return 1;
        }
    }

    if (length < capacity && feof(stdin)) {
        return 1;
    }

    buffer[0] = '\0';

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char discard[256];

        if (fgets(discard, (int)sizeof discard, stdin) == NULL) {
            return ferror(stdin) ? -1 : 0;
        }

        for (length = 0U; length < sizeof discard &&
                          discard[length] != '\0'; ++length) {
            if (discard[length] == '\n') {
                return 0;
            }
        }
    }
}

static int is_hexadecimal(const char *text)
{
    size_t index = 0U;

    if (text == NULL || text[0] == '\0') {
        return 0;
    }

    if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) {
        index = 2U;
    }

    if (text[index] == '\0') {
        return 0;
    }

    while (text[index] != '\0') {
        if (!is_hex_digit((unsigned char)text[index])) {
            return 0;
        }
        ++index;
    }

    return 1;
}

static int is_hex_even(const char *text)
{
    size_t length = 0U;
    unsigned char last_digit;

    if (text == NULL || text[0] == '\0') {
        return 0;
    }

    while (text[length] != '\0') {
        ++length;
    }

    last_digit = (unsigned char)text[length - 1U];

    return last_digit == (unsigned char)'0' ||
           last_digit == (unsigned char)'2' ||
           last_digit == (unsigned char)'4' ||
           last_digit == (unsigned char)'6' ||
           last_digit == (unsigned char)'8' ||
           last_digit == (unsigned char)'a' ||
           last_digit == (unsigned char)'c' ||
           last_digit == (unsigned char)'e' ||
           last_digit == (unsigned char)'A' ||
           last_digit == (unsigned char)'C' ||
           last_digit == (unsigned char)'E';
}

int main(void)
{
    char *input;
    int status;
    int result = EXIT_FAILURE;

    input = malloc(INPUT_CAPACITY);
    if (input == NULL) {
        fputs("Memory allocation error\n", stderr);
        return EXIT_FAILURE;
    }

    status = read_line(input, INPUT_CAPACITY);

    if (status < 0) {
        fputs("Input error\n", stderr);
    } else if (status == 0) {
        fputs("Input too long\n", stderr);
    } else if (!is_hexadecimal(input)) {
        fputs("Invalid hexadecimal number\n", stderr);
    } else {
        puts(is_hex_even(input) ? "Even" : "Odd");
        result = EXIT_SUCCESS;
    }

    free(input);
    return result;
}
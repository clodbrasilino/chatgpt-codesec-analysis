#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 128U
#define OCTAL_BUFFER_SIZE 23U

static int decimal_to_octal(uint64_t value, char *output, size_t output_size)
{
    char reversed[OCTAL_BUFFER_SIZE];
    size_t length = 0U;

    if (output == NULL || output_size == 0U) {
        return -1;
    }

    do {
        if (length >= sizeof(reversed)) {
            output[0] = '\0';
            return -1;
        }

        reversed[length++] = (char)('0' + (value & UINT64_C(7)));
        value >>= 3U;
    } while (value != UINT64_C(0));

    if (length + 1U > output_size) {
        output[0] = '\0';
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        output[i] = reversed[length - i - 1U];
    }

    output[length] = '\0';
    return 0;
}

static int read_line(char *buffer, size_t buffer_size)
{
    size_t length = 0U;
    int ch;

    if (buffer == NULL || buffer_size < 2U) {
        return -1;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1U < buffer_size) {
            buffer[length++] = (char)ch;
        } else {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            buffer[0] = '\0';

            if (ch == EOF && ferror(stdin)) {
                return -1;
            }

            return -1;
        }
    }

    if (ch == EOF && (ferror(stdin) || length == 0U)) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[length] = '\0';
    return 0;
}

int main(void)
{
    char input[INPUT_BUFFER_SIZE];
    char octal[OCTAL_BUFFER_SIZE];
    char *start;
    char *end;
    uintmax_t parsed;

    if (fputs("Enter a non-negative decimal number: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (read_line(input, sizeof(input)) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;

    while (*start != '\0' && isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (decimal_to_octal((uint64_t)parsed, octal, sizeof(octal)) != 0) {
        fputs("Conversion failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Octal: %s\n", octal) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINT64_OCTAL_DIGITS 22U
#define OCTAL_BUFFER_SIZE (UINT64_OCTAL_DIGITS + 1U)
#define INPUT_BUFFER_SIZE 128U

static int decimal_to_octal(uint64_t value, char *output, size_t output_size)
{
    int written;

    if (output == NULL || output_size == 0U) {
        return -1;
    }

    written = snprintf(output, output_size, "%" PRIo64, value);

    if (written < 0 || (size_t)written >= output_size) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

static int is_space_character(unsigned char character)
{
    return character == (unsigned char)' ' ||
           character == (unsigned char)'\t' ||
           character == (unsigned char)'\n' ||
           character == (unsigned char)'\r' ||
           character == (unsigned char)'\f' ||
           character == (unsigned char)'\v';
}

static int discard_line(FILE *stream)
{
    int character;

    if (stream == NULL) {
        return -1;
    }

    do {
        character = fgetc(stream);
    } while (character != '\n' && character != EOF);

    return character == EOF && ferror(stream) ? -1 : 0;
}

int main(void)
{
    char input[INPUT_BUFFER_SIZE];
    char octal[OCTAL_BUFFER_SIZE];
    char *start;
    char *end;
    uintmax_t parsed_value;
    size_t length;

    if (fputs("Enter a non-negative decimal number: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs(ferror(stdin) ? "Input error.\n" : "Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    for (length = 0U;
         length < sizeof input && input[length] != '\0';
         ++length) {
    }

    if (length == sizeof input) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0U && input[length - 1U] == '\n') {
        input[--length] = '\0';

        if (length > 0U && input[length - 1U] == '\r') {
            input[--length] = '\0';
        }
    } else if (!feof(stdin)) {
        if (discard_line(stdin) != 0) {
            fputs("Input error.\n", stderr);
        } else {
            fputs("Invalid input.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    start = input;

    while (*start != '\0' &&
           is_space_character((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoumax(start, &end, 10);

    if (end == start ||
        errno == ERANGE ||
        parsed_value > (uintmax_t)UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' &&
           is_space_character((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (decimal_to_octal((uint64_t)parsed_value,
                         octal,
                         sizeof octal) != 0) {
        fputs("Conversion failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs("Octal: ", stdout) == EOF ||
        fputs(octal, stdout) == EOF ||
        fputc('\n', stdout) == EOF) {
        fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
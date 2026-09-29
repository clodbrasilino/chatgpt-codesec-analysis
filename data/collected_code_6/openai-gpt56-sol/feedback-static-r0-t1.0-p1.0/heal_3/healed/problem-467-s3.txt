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

    if (output == NULL || output_size < OCTAL_BUFFER_SIZE) {
        return -1;
    }

    written = snprintf(output, output_size, "%" PRIo64, value);

    if (written < 0 || (size_t)written >= output_size) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

static int is_space_character(char character)
{
    return character == ' ' || character == '\t' || character == '\n' ||
           character == '\r' || character == '\f' || character == '\v';
}

int main(void)
{
    char input[INPUT_BUFFER_SIZE];
    char octal[OCTAL_BUFFER_SIZE];
    char *end;
    uintmax_t parsed_value;
    size_t length = 0U;

    fputs("Enter a non-negative decimal number: ", stdout);

    if (fflush(stdout) == EOF) {
        fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (length < sizeof input && input[length] != '\0') {
        ++length;
    }

    if (length == sizeof input) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0U && input[length - 1U] != '\n' && !feof(stdin)) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    end = input;

    while (is_space_character(*end)) {
        ++end;
    }

    if (*end == '-' || *end == '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoumax(end, &end, 10);

    if (errno == ERANGE || parsed_value > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (is_space_character(*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (decimal_to_octal((uint64_t)parsed_value, octal, sizeof octal) != 0) {
        fputs("Conversion failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Octal: %s\n", octal) < 0) {
        fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
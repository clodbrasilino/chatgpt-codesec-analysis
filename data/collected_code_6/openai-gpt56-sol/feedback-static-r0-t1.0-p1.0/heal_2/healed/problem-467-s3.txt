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
    if (output == NULL || output_size < OCTAL_BUFFER_SIZE) {
        return -1;
    }

    int written = snprintf(output, output_size, "%" PRIo64, value);

    if (written < 0 || (size_t)written >= output_size) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[INPUT_BUFFER_SIZE];
    char octal[OCTAL_BUFFER_SIZE];
    char *end;
    uintmax_t parsed_value;

    fputs("Enter a non-negative decimal number: ", stdout);
    fflush(stdout);

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[0] != '\0' && input[strlen(input) - 1U] != '\n' && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = input;

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end == '-' || *end == '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    parsed_value = strtoumax(end, &end, 10);

    if (errno == ERANGE || parsed_value > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
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

    printf("Octal: %s\n", octal);
    return EXIT_SUCCESS;
}
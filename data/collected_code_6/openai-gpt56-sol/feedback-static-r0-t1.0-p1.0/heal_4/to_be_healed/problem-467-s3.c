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

    /* Possible weaknesses found:
     * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
     */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
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
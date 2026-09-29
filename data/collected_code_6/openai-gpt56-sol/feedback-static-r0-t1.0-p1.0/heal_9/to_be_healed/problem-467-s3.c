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
    static const char format[] = "%" PRIo64;
    int written;

    if (output == NULL || output_size == 0U) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
     */
    written = snprintf(output, output_size, format, value);

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

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != '\n' && character != EOF) {
    }

    if (character == EOF && ferror(stream)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char octal[OCTAL_BUFFER_SIZE] = {0};
    char *start;
    char *end;
    uintmax_t parsed_value;
    size_t length = 0U;

    if (fputs("Enter a non-negative decimal number: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        (void)fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)sizeof input, stdin) == NULL) {
        (void)fputs(ferror(stdin) ? "Input error.\n" : "Invalid input.\n",
                    stderr);
        return EXIT_FAILURE;
    }

    while (length < sizeof input && input[length] != '\0') {
        ++length;
    }

    if (length == sizeof input) {
        (void)fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0U && input[length - 1U] == '\n') {
        input[--length] = '\0';

        if (length > 0U && input[length - 1U] == '\r') {
            input[--length] = '\0';
        }
    } else if (!feof(stdin)) {
        if (discard_line(stdin) != 0) {
            (void)fputs("Input error.\n", stderr);
        } else {
            (void)fputs("Invalid input.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    start = input;

    while (*start != '\0' &&
           is_space_character((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        (void)fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoumax(start, &end, 10);

    if (end == start ||
        errno == ERANGE ||
        parsed_value > (uintmax_t)UINT64_MAX) {
        (void)fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' &&
           is_space_character((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        (void)fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (decimal_to_octal((uint64_t)parsed_value,
                         octal,
                         sizeof octal) != 0) {
        (void)fputs("Conversion failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs("Octal: ", stdout) == EOF ||
        fputs(octal, stdout) == EOF ||
        fputc('\n', stdout) == EOF) {
        (void)fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
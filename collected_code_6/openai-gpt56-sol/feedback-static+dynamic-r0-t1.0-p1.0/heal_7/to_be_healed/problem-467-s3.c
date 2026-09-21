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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char reversed[OCTAL_BUFFER_SIZE];
    size_t length = 0U;

    if (output == NULL || output_size == 0U) {
        return -1;
    }

    do {
        if (length >= sizeof(reversed)) {
            return -1;
        }

        reversed[length++] = (char)('0' + (value & UINT64_C(7)));
        value >>= 3;
    } while (value != 0U);

    if (length >= output_size) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        output[i] = reversed[length - i - 1U];
    }

    output[length] = '\0';
    return 0;
}

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return (ch == EOF && ferror(stdin)) ? -1 : 0;
}

static int read_line(char *buffer, size_t buffer_size)
{
    size_t length = 0U;
    int ch;

    if (buffer == NULL || buffer_size < 2U) {
        return -1;
    }

    while (length + 1U < buffer_size) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch == '\n') {
            buffer[length] = '\0';
            return 0;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0U) {
                buffer[0] = '\0';
                return -1;
            }

            buffer[length] = '\0';
            return 0;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = getchar();
    if (ch == '\n') {
        return 0;
    }

    if (ch == EOF) {
        if (ferror(stdin)) {
            buffer[0] = '\0';
            return -1;
        }

        return 0;
    }

    if (discard_line() != 0) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[0] = '\0';
    return -1;
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

    while (*start != '\0' && isspace((unsigned char)*start)) {
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

    while (*end != '\0' && isspace((unsigned char)*end)) {
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
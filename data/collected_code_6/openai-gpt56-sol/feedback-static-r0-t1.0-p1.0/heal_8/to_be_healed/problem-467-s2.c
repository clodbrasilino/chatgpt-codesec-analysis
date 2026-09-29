#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 128U
#define OCTAL_BUFFER_SIZE 23U

static int decimal_to_octal(uint64_t value, char *output, size_t output_size)
{
    int result;

    if (output == NULL || output_size == 0U) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
     */
    result = snprintf(output, output_size, "%" PRIo64, value);
    if (result < 0 || (size_t)result >= output_size) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

static int read_line(char *buffer, size_t buffer_size)
{
    size_t length;
    int ch;

    if (buffer == NULL || buffer_size < 2U) {
        return -1;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return -1;
    }

    length = 0U;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return 0;
    }

    if (feof(stdin)) {
        return length > 0U ? 0 : -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    buffer[0] = '\0';
    return -1;
}

static int is_horizontal_space(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r' ||
           ch == '\v' || ch == '\f';
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
    uintmax_t value;

    if (fputs("Enter a non-negative decimal integer: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (read_line(input, sizeof(input)) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (is_horizontal_space(*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || value > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (is_horizontal_space(*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (decimal_to_octal((uint64_t)value, octal, sizeof(octal)) != 0) {
        fputs("Conversion failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs("Octal: ", stdout) == EOF ||
        fputs(octal, stdout) == EOF ||
        fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
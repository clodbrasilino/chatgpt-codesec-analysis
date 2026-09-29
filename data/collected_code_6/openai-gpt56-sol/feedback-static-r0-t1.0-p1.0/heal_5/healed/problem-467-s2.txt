#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 128U
#define OCTAL_BUFFER_SIZE ((sizeof(uint64_t) * 8U + 2U) / 3U + 1U)

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

static int discard_line(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == EOF && ferror(stdin) ? -1 : 0;
}

static int read_line(char *buffer, size_t buffer_size)
{
    size_t length;

    if (buffer == NULL || buffer_size < 2U || buffer_size > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return -1;
    }

    length = 0U;
    while (buffer[length] != '\0') {
        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            return 0;
        }
        ++length;
    }

    if (feof(stdin)) {
        return length == 0U ? -1 : 0;
    }

    if (discard_line() != 0) {
        return -1;
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
    char input[INPUT_BUFFER_SIZE] = {0};
    char octal[OCTAL_BUFFER_SIZE] = {0};
    char *start;
    char *end;
    uintmax_t parsed_value;

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

    if (*start == '\0' || *start == '-' || *start == '+') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed_value > UINT64_MAX) {
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

    if (decimal_to_octal((uint64_t)parsed_value, octal, sizeof(octal)) != 0) {
        fputs("Conversion failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Octal: %s\n", octal) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
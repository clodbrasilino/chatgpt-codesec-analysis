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

    if (buffer == NULL || buffer_size < 2U) {
        return -1;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return -1;
    }

    for (length = 0U; buffer[length] != '\0'; ++length) {
        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            return 0;
        }
    }

    if (feof(stdin)) {
        return 0;
    }

    for (;;) {
        char discard[INPUT_BUFFER_SIZE];

        if (fgets(discard, (int)sizeof(discard), stdin) == NULL) {
            break;
        }

        for (length = 0U; discard[length] != '\0'; ++length) {
            if (discard[length] == '\n') {
                buffer[0] = '\0';
                return -1;
            }
        }
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
    while (*start != '\0' && is_horizontal_space(*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || value > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && is_horizontal_space(*end)) {
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
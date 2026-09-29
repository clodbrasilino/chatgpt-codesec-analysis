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

int main(void)
{
    char input[INPUT_BUFFER_SIZE];
    char octal[OCTAL_BUFFER_SIZE];
    char *end = NULL;
    uintmax_t parsed_value;

    fputs("Enter a non-negative decimal integer: ", stdout);
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[0] != '\0' && input[0] != '\n') {
        size_t length = 0U;

        while (length < sizeof(input) && input[length] != '\0' &&
               input[length] != '\n') {
            ++length;
        }

        if (length == sizeof(input) || input[length] != '\n') {
            int ch;

            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            fputs("Invalid input.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    parsed_value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed_value > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0' || input[0] == '-') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (decimal_to_octal((uint64_t)parsed_value, octal, sizeof(octal)) != 0) {
        fputs("Conversion failed.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Octal: %s\n", octal);
    return EXIT_SUCCESS;
}
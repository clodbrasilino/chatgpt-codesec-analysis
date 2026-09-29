#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t set_even_bits(uint32_t value)
{
    return value | UINT32_C(0x55555555);
}

static int read_line(char *buffer, size_t size)
{
    if (size < 2 || fgets(buffer, size, stdin) == NULL) {
        return 0;
    }

    size_t length = 0;
    while (length < size && buffer[length] != '\0') {
        ++length;
    }

    if (length == size) {
        return 0;
    }

    if (length > 0 && buffer[length - 1] == '\n') {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int ch = fgetc(stdin);
    if (ch == '\n' || ch == EOF) {
        return 1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *end;
    uintmax_t parsed_value;

    if (!read_line(input, sizeof input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed_value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed_value > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu32 "\n",
               set_even_bits((uint32_t)parsed_value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
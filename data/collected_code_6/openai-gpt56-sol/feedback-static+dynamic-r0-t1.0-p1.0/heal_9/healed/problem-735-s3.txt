#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t toggle_inner_bits(uint32_t value)
{
    uint32_t highest_bit = UINT32_C(1);

    if (value <= UINT32_C(1)) {
        return value;
    }

    while (highest_bit <= value / UINT32_C(2)) {
        highest_bit <<= 1;
    }

    return value ^ (highest_bit - UINT32_C(2));
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t parsed;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    char *newline = NULL;

    for (size_t i = 0; i < sizeof input; ++i) {
        if (input[i] == '\n') {
            newline = &input[i];
            break;
        }

        if (input[i] == '\0') {
            break;
        }
    }

    if (newline != NULL) {
        *newline = '\0';
    } else {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu32 "\n",
               toggle_inner_bits((uint32_t)parsed)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
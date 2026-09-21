#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define OCTAL_BUFFER_SIZE (((sizeof(uint64_t) * CHAR_BIT) + 2U) / 3U + 1U)

static int decimal_to_octal(uint64_t value, char *output, size_t output_size)
{
    size_t length = 1U;
    uint64_t temporary = value;

    while (temporary >= UINT64_C(8)) {
        temporary /= UINT64_C(8);
        ++length;
    }

    if (output == NULL || output_size < length + 1U) {
        return -1;
    }

    output[length] = '\0';

    do {
        output[--length] = (char)('0' + (value % UINT64_C(8)));
        value /= UINT64_C(8);
    } while (length > 0U);

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    char *start;
    char *end;
    uintmax_t parsed;
    char octal[OCTAL_BUFFER_SIZE];
    int result = EXIT_FAILURE;

    fputs("Enter a non-negative decimal integer: ", stdout);
    fflush(stdout);

    if (getline(&input, &capacity, stdin) < 0) {
        fputs("Invalid input.\n", stderr);
        goto cleanup;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        fputs("Invalid input.\n", stderr);
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        goto cleanup;
    }

    if (decimal_to_octal((uint64_t)parsed, octal, sizeof octal) != 0) {
        fputs("Conversion failed.\n", stderr);
        goto cleanup;
    }

    printf("Octal: %s\n", octal);
    result = EXIT_SUCCESS;

cleanup:
    free(input);
    return result;
}
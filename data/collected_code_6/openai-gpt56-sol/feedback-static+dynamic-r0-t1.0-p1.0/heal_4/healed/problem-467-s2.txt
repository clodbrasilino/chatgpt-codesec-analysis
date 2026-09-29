#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int decimal_to_octal(uint64_t value, char **output)
{
    size_t length = 1;
    uint64_t temporary = value;
    char *buffer;
    size_t position;

    if (output == NULL) {
        return -1;
    }

    while (temporary >= UINT64_C(8)) {
        temporary /= UINT64_C(8);
        ++length;
    }

    buffer = malloc(length + 1);
    if (buffer == NULL) {
        return -1;
    }

    buffer[length] = '\0';
    position = length;

    do {
        buffer[--position] = (char)('0' + (value % UINT64_C(8)));
        value /= UINT64_C(8);
    } while (position > 0);

    *output = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *octal = NULL;
    char *start;
    char *end;
    size_t capacity = 0;
    uintmax_t parsed;
    int result = EXIT_FAILURE;

    fputs("Enter a non-negative decimal integer: ", stdout);
    if (fflush(stdout) == EOF) {
        goto cleanup;
    }

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

    if (decimal_to_octal((uint64_t)parsed, &octal) != 0) {
        fputs("Conversion failed.\n", stderr);
        goto cleanup;
    }

    if (printf("Octal: %s\n", octal) < 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(octal);
    free(input);
    return result;
}
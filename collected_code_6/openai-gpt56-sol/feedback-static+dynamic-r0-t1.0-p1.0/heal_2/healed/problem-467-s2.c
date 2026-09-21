#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define OCTAL_BUFFER_SIZE ((sizeof(uint64_t) * CHAR_BIT + 2U) / 3U + 1U)
#define INPUT_BUFFER_SIZE 128U

#include <limits.h>

static int decimal_to_octal(uint64_t value, char *output, size_t output_size)
{
    size_t length = 1U;
    uint64_t temporary = value;

    while (temporary >= UINT64_C(8)) {
        temporary /= UINT64_C(8);
        ++length;
    }

    if (output == NULL || output_size <= length) {
        return -1;
    }

    output[length] = '\0';

    do {
        output[--length] = (char)('0' + (value % UINT64_C(8)));
        value /= UINT64_C(8);
    } while (length != 0U);

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    char octal[OCTAL_BUFFER_SIZE];
    char *end = NULL;
    uintmax_t parsed;
    int result = EXIT_FAILURE;

    printf("Enter a non-negative decimal integer: ");
    fflush(stdout);

    if (getline(&input, &capacity, stdin) < 0) {
        fprintf(stderr, "Invalid input.\n");
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid input.\n");
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || input[0] == '-') {
        fprintf(stderr, "Invalid input.\n");
        goto cleanup;
    }

    if (decimal_to_octal((uint64_t)parsed, octal, sizeof(octal)) != 0) {
        fprintf(stderr, "Conversion failed.\n");
        goto cleanup;
    }

    printf("Octal: %s\n", octal);
    result = EXIT_SUCCESS;

cleanup:
    free(input);
    return result;
}
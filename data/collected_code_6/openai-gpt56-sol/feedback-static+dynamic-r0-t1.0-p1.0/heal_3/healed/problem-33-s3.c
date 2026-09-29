#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *decimal_to_binary(uint64_t value)
{
    char *result = malloc(65);
    if (result == NULL) {
        return NULL;
    }

    size_t bit_count = 1;
    uint64_t temp = value;

    while ((temp >>= 1) != 0) {
        ++bit_count;
    }

    result[bit_count] = '\0';

    for (size_t i = bit_count; i > 0; --i) {
        result[i - 1] = (char)('0' + (value & UINT64_C(1)));
        value >>= 1;
    }

    return result;
}

int main(void)
{
    char input[128];

    printf("Enter a non-negative decimal number: ");
    fflush(stdout);

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else if (length == sizeof input || !feof(stdin)) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    char *start = input;
    while (*start == ' ' || *start == '\t' || *start == '\r' ||
           *start == '\n' || *start == '\f' || *start == '\v') {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed_value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed_value > UINT64_MAX) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    char *binary = decimal_to_binary((uint64_t)parsed_value);
    if (binary == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Binary: %s\n", binary);

    free(binary);
    return EXIT_SUCCESS;
}
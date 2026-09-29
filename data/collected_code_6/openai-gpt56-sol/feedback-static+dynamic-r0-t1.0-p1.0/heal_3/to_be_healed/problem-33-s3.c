#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *decimal_to_binary(uint64_t value)
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
    char *input = malloc(128);

    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Enter a non-negative decimal number: ");
    fflush(stdout);

    if (fgets(input, 128, stdin) == NULL) {
        fprintf(stderr, "Invalid input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    char *newline = input;
    while (*newline != '\0' && *newline != '\n') {
        ++newline;
    }

    if (*newline != '\n' && !feof(stdin)) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fprintf(stderr, "Invalid input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    char *start = input;

    while (*start == ' ' || *start == '\t' ||
           *start == '\r' || *start == '\n' ||
           *start == '\f' || *start == '\v') {
        ++start;
    }

    if (*start == '-') {
        fprintf(stderr, "Invalid input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    uintmax_t parsed_value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed_value > UINT64_MAX) {
        fprintf(stderr, "Invalid input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' ||
           *end == '\r' || *end == '\n' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fprintf(stderr, "Invalid input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    char *binary = decimal_to_binary((uint64_t)parsed_value);

    if (binary == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Binary: %s\n", binary);

    free(binary);
    free(input);
    return EXIT_SUCCESS;
}
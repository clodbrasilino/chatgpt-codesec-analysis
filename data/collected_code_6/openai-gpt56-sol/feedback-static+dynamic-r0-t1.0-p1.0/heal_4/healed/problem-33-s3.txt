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

static int read_value(uint64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return 0;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    char *start = line;
    while (*start == ' ' || *start == '\t' || *start == '\r' ||
           *start == '\n' || *start == '\f' || *start == '\v') {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        free(line);
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT64_MAX) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = (uint64_t)parsed;
    free(line);
    return 1;
}

int main(void)
{
    uint64_t value;

    fputs("Enter a non-negative decimal number: ", stdout);
    fflush(stdout);

    if (!read_value(&value)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    char *binary = decimal_to_binary(value);
    if (binary == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Binary: %s\n", binary);
    free(binary);

    return EXIT_SUCCESS;
}
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t count_divisors(uint64_t value)
{
    uint64_t count = 0;

    for (uint64_t divisor = 1; divisor <= value / divisor; ++divisor) {
        if (value % divisor == 0) {
            count += divisor == value / divisor ? UINT64_C(1) : UINT64_C(2);
        }
    }

    return count;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 32 : capacity * 2;

            if (new_capacity < capacity || new_capacity > SIZE_MAX - 1) {
                free(line);
                fputs("Input is too large.\n", stderr);
                return EXIT_FAILURE;
            }

            char *new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(line);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0 && character == EOF) {
        free(line);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        if (capacity == SIZE_MAX) {
            free(line);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        char *new_line = realloc(line, length + 1);
        if (new_line == NULL) {
            free(line);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        line = new_line;
    }

    line[length] = '\0';

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(line, &end, 10);

    if (errno == ERANGE || end == line || value == 0 || value > UINT64_MAX) {
        free(line);
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t result = count_divisors((uint64_t)value);
    free(line);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
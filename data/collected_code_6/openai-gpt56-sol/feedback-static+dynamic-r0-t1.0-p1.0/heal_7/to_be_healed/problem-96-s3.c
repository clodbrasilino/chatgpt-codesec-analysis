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
    size_t length = 0;
    size_t capacity = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 32;
            } else {
                if (capacity > (SIZE_MAX - 1) / 2) {
                    free(line);
                    fputs("Input is too large.\n", stderr);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2;
            }

            char *temporary = realloc(line, new_capacity);
            if (temporary == NULL) {
                free(line);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            line = temporary;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(line);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0 && character == EOF) {
        free(line);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == SIZE_MAX) {
        free(line);
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (capacity <= length) {
        char *temporary = realloc(line, length + 1);
        if (temporary == NULL) {
            free(line);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        line = temporary;
    }

    line[length] = '\0';

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(line, &end, 10);

    if (errno == ERANGE || end == line || parsed == 0 ||
        parsed > UINT64_MAX || line[0] == '-') {
        free(line);
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t result = count_divisors((uint64_t)parsed);
    free(line);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
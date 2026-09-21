#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 4096 };

static int sum_even_factors(uint64_t number, uint64_t *sum)
{
    uint64_t total = 0;

    if (number == 0 || sum == NULL) {
        return -1;
    }

    for (uint64_t factor = 1; factor <= number / factor; ++factor) {
        if (number % factor == 0) {
            uint64_t paired_factor = number / factor;

            if ((factor & UINT64_C(1)) == 0) {
                if (factor > UINT64_MAX - total) {
                    return -1;
                }
                total += factor;
            }

            if (paired_factor != factor &&
                (paired_factor & UINT64_C(1)) == 0) {
                if (paired_factor > UINT64_MAX - total) {
                    return -1;
                }
                total += paired_factor;
            }
        }
    }

    *sum = total;
    return 0;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    return 0;
}

static int read_line(char **line)
{
    char *buffer;
    size_t capacity = (size_t)MAX_INPUT_LENGTH + 2U;
    size_t length = 0;

    if (line == NULL || capacity > (size_t)INT_MAX) {
        return -1;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        return -1;
    }

    while (length < capacity && buffer[length] != '\0') {
        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            *line = buffer;
            return 0;
        }
        ++length;
    }

    if (length > (size_t)MAX_INPUT_LENGTH) {
        if (discard_line() != 0) {
            free(buffer);
            return -1;
        }

        free(buffer);
        return -1;
    }

    if (ferror(stdin)) {
        free(buffer);
        return -1;
    }

    *line = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *start;
    char *end;
    uintmax_t parsed_number;
    uint64_t number;
    uint64_t sum;

    if (read_line(&input) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_number = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed_number == 0 ||
        parsed_number > UINT64_MAX) {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    number = (uint64_t)parsed_number;
    free(input);

    if (sum_even_factors(number, &sum) != 0) {
        fputs("Unable to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
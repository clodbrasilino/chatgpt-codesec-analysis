#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_factors(uint64_t number, uint64_t *sum)
{
    uint64_t total = 0;

    if (number == 0 || sum == NULL) {
        return -1;
    }

    for (uint64_t factor = 1; factor <= number / factor; ++factor) {
        uint64_t paired_factor;

        if (number % factor != 0) {
            continue;
        }

        paired_factor = number / factor;

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

    *sum = total;
    return 0;
}

static int read_line(char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch;

        if (length == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *input;
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
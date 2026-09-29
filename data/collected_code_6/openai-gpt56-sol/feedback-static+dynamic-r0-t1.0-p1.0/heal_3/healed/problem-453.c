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
        if (number % factor != 0) {
            continue;
        }

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

    *sum = total;
    return 0;
}

static int read_line(char *buffer, size_t size)
{
    size_t length;

    if (buffer == NULL || size < 2) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    length = 0;
    while (length < size && buffer[length] != '\0') {
        ++length;
    }

    if (length == size) {
        return -1;
    }

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
        return 0;
    }

    if (feof(stdin)) {
        return 0;
    }

    for (;;) {
        int ch = getchar();

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin)) {
                return -1;
            }
            break;
        }
    }

    return 1;
}

int main(void)
{
    char input[128];
    char *start;
    char *end;
    uintmax_t parsed_number;
    uint64_t number;
    uint64_t sum;
    int read_status;

    read_status = read_line(input, sizeof input);
    if (read_status < 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_status > 0) {
        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed_number = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed_number == 0 ||
        parsed_number > UINT64_MAX) {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    number = (uint64_t)parsed_number;

    if (sum_even_factors(number, &sum) != 0) {
        fputs("Unable to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
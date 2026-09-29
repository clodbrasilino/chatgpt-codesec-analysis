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

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *start;
    char *end;
    uintmax_t parsed_number;
    uint64_t number;
    uint64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (length < sizeof input && input[length] != '\0') {
        ++length;
    }

    if (length == 0 || length == sizeof input) {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (!feof(stdin)) {
        int ch;
        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
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

    while (isspace((unsigned char)*end)) {
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
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_odd_factors(uint64_t number, uint64_t *result)
{
    uint64_t sum = UINT64_C(1);

    if (number == 0 || result == NULL) {
        return 0;
    }

    while ((number & UINT64_C(1)) == 0) {
        number >>= 1;
    }

    for (uint64_t factor = UINT64_C(3);
         factor <= number / factor;
         factor += UINT64_C(2)) {
        uint64_t term = UINT64_C(1);
        uint64_t power = UINT64_C(1);

        while (number % factor == 0) {
            number /= factor;

            if (power > UINT64_MAX / factor) {
                return 0;
            }
            power *= factor;

            if (term > UINT64_MAX - power) {
                return 0;
            }
            term += power;
        }

        if (sum > UINT64_MAX / term) {
            return 0;
        }
        sum *= term;
    }

    if (number > UINT64_C(1)) {
        uint64_t term;

        if (number == UINT64_MAX) {
            return 0;
        }

        term = number + UINT64_C(1);

        if (sum > UINT64_MAX / term) {
            return 0;
        }
        sum *= term;
    }

    *result = sum;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char input[256];
    char *end;
    uintmax_t parsed;
    size_t length;

    if (value == NULL) {
        return 0;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (length < sizeof input && input[length] != '\0') {
        ++length;
    }

    if (length == sizeof input) {
        return 0;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';

        if (length > 0 && input[length - 1] == '\r') {
            input[--length] = '\0';
        }
    } else if (!feof(stdin)) {
        int character;

        do {
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed == 0 ||
        parsed > UINT64_MAX) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(void)
{
    uint64_t number;
    uint64_t result;

    if (!read_uint64(&number)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_odd_factors(number, &result)) {
        fputs("The sum cannot be represented as uint64_t.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
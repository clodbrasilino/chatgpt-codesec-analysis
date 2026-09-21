#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_prime_divisors(uint64_t number, uint64_t *sum)
{
    uint64_t result = 0;

    if (sum == NULL || number < 2) {
        return 0;
    }

    if (number % 2 == 0) {
        result = 2;
        do {
            number /= 2;
        } while (number % 2 == 0);
    }

    for (uint64_t divisor = 3;
         divisor <= number / divisor;
         divisor += 2) {
        if (number % divisor == 0) {
            if (UINT64_MAX - result < divisor) {
                return 0;
            }

            result += divisor;

            do {
                number /= divisor;
            } while (number % divisor == 0);
        }
    }

    if (number > 1) {
        if (UINT64_MAX - result < number) {
            return 0;
        }

        result += number;
    }

    *sum = result;
    return 1;
}

int main(void)
{
    enum { INPUT_SIZE = 128 };
    char input[INPUT_SIZE];
    char *end;
    uintmax_t value;
    uint64_t sum;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    end = input;
    while (*end != '\0' && *end != '\n') {
        end++;
    }

    if (*end == '\n') {
        *end = '\0';
    } else if (*end == '\0') {
        ch = fgetc(stdin);
        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        end++;
    }

    if (*end != '\0' || value < 2) {
        return EXIT_FAILURE;
    }

    if (!sum_prime_divisors((uint64_t)value, &sum)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
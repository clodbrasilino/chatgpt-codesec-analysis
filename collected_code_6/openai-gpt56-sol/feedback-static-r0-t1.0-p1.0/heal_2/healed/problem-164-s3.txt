#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_proper_divisors(uint64_t number, uint64_t *sum)
{
    uint64_t result = 1;

    if (sum == NULL || number == 0) {
        return 0;
    }

    if (number == 1) {
        *sum = 0;
        return 1;
    }

    for (uint64_t divisor = 2; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0) {
            uint64_t quotient = number / divisor;

            if (UINT64_MAX - result < divisor) {
                return 0;
            }
            result += divisor;

            if (quotient != divisor) {
                if (UINT64_MAX - result < quotient) {
                    return 0;
                }
                result += quotient;
            }
        }
    }

    *sum = result;
    return 1;
}

static int parse_uint64(const char **input, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    while (isspace((unsigned char)**input)) {
        ++*input;
    }

    if (**input == '\0' || **input == '-' || **input == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*input, &end, 10);

    if (end == *input || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *input = end;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    const char *cursor;
    uint64_t first;
    uint64_t second;
    uint64_t first_sum;
    uint64_t second_sum;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            char *resized;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Unable to allocate memory\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && length == 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        size_t new_capacity = capacity == 0 ? 1 : capacity + 1;
        char *resized;

        if (new_capacity <= capacity) {
            free(input);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        resized = realloc(input, new_capacity);
        if (resized == NULL) {
            free(input);
            fputs("Unable to allocate memory\n", stderr);
            return EXIT_FAILURE;
        }

        input = resized;
        capacity = new_capacity;
    }

    input[length] = '\0';
    cursor = input;

    if (!parse_uint64(&cursor, &first) ||
        !parse_uint64(&cursor, &second)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!sum_of_proper_divisors(first, &first_sum) ||
        !sum_of_proper_divisors(second, &second_sum)) {
        fputs("Unable to calculate divisor sums\n", stderr);
        return EXIT_FAILURE;
    }

    puts(first_sum == second_sum ? "Same" : "Not same");
    return EXIT_SUCCESS;
}
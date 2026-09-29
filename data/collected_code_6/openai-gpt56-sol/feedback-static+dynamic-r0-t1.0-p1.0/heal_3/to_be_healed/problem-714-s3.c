#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_distinct_prime_power_factors(uint64_t number)
{
    size_t count = 0;

    if (number < 2) {
        return 0;
    }

    if (number % 2 == 0) {
        ++count;
        do {
            number /= 2;
        } while (number % 2 == 0);
    }

    for (uint64_t divisor = 3; divisor <= number / divisor; divisor += 2) {
        if (number % divisor == 0) {
            ++count;
            do {
                number /= divisor;
            } while (number % divisor == 0);
        }
    }

    if (number > 1) {
        ++count;
    }

    return count;
}

static int is_space_character(char character)
{
    return character == ' ' || character == '\t' ||
           character == '\r' || character == '\n' ||
           character == '\v' || character == '\f';
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != EOF && character != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin) || (length == 0 && character == EOF)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = capacity == 0 ? 2 : capacity + 1;
        char *new_input = realloc(input, new_capacity);

        if (new_input == NULL) {
            free(input);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        input = new_input;
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         */
        capacity = new_capacity;
    }

    input[length] = '\0';

    char *start = input;
    while (is_space_character(*start)) {
        ++start;
    }

    if (*start == '-') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || value > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (is_space_character(*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    printf("%zu\n",
           count_distinct_prime_power_factors((uint64_t)value));

    return EXIT_SUCCESS;
}
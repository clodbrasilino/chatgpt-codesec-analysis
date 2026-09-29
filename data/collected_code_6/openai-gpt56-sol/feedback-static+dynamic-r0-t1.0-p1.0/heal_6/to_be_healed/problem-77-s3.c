#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int64_t digit_sum_difference(uint64_t number)
{
    int64_t difference = 0;

    do {
        uint64_t digit = number % UINT64_C(10);
        difference += (digit % UINT64_C(2) == 0)
                          ? (int64_t)digit
                          : -(int64_t)digit;
        number /= UINT64_C(10);
    } while (number != 0);

    return difference;
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
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length == SIZE_MAX - 1) {
            free(input);
            fputs("Input too long.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 32;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Input too long.\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0 && character == EOF) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (capacity <= length) {
        char *new_input = realloc(input, length + 1);
        if (new_input == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }
        input = new_input;
    }

    input[length] = '\0';

    char *start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end;
    uintmax_t value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value > UINT64_MAX) {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", digit_sum_difference((uint64_t)value));

    free(input);
    return EXIT_SUCCESS;
}
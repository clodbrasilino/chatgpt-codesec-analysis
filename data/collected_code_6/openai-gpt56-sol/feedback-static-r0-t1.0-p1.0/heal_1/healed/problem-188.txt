#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_perfect_square(uint64_t number)
{
    uint64_t low = 0;
    uint64_t high = UINT64_C(4294967295);

    if (number < high) {
        high = number;
    }

    while (low <= high) {
        uint64_t mid = low + (high - low) / 2;
        uint64_t quotient;

        if (mid == 0) {
            if (number == 0) {
                return true;
            }
            low = 1;
            continue;
        }

        quotient = number / mid;

        if (mid == quotient && number % mid == 0) {
            return true;
        }

        if (mid < quotient) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return false;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;
    char *end;
    uintmax_t value;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        char *resized;

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0 && character == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;
        char *resized = realloc(input, new_capacity);

        if (resized == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = resized;
        capacity = new_capacity;
    }

    input[length] = '\0';

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 10);

    if (errno != 0 || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || value > UINT64_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_perfect_square((uint64_t)value) ? "Yes" : "No");

    free(input);
    return EXIT_SUCCESS;
}
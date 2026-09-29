#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_armstrong(unsigned long long number)
{
    unsigned long long temp = number;
    unsigned long long sum = 0ULL;
    unsigned int digits = 0U;

    do {
        ++digits;
        temp /= 10ULL;
    } while (temp != 0ULL);

    temp = number;

    do {
        const unsigned long long digit = temp % 10ULL;
        unsigned long long power = 1ULL;

        for (unsigned int i = 0U; i < digits; ++i) {
            if (digit != 0ULL && power > ULLONG_MAX / digit) {
                return false;
            }
            power *= digit;
        }

        if (sum > ULLONG_MAX - power) {
            return false;
        }

        sum += power;
        temp /= 10ULL;
    } while (temp != 0ULL);

    return sum == number;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 32U : capacity * 2U;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0U) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length + 1U >= capacity) {
        size_t new_capacity = length + 1U;
        char *new_input = realloc(input, new_capacity);

        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
        capacity = new_capacity;
    }

    input[length] = '\0';

    char *start = input;

    while (*start == ' ' || *start == '\t' || *start == '\r' ||
           *start == '\f' || *start == '\v') {
        ++start;
    }

    if (*start == '-') {
        puts("Not an Armstrong number");
        free(input);
        return EXIT_SUCCESS;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_armstrong(number)
             ? "Armstrong number"
             : "Not an Armstrong number");

    free(input);
    return EXIT_SUCCESS;
}
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_armstrong(unsigned long long number)
{
    unsigned long long value = number;
    unsigned long long sum = 0;
    unsigned int digits = 0;

    do {
        ++digits;
        value /= 10;
    } while (value != 0);

    value = number;

    do {
        unsigned long long digit = value % 10;
        unsigned long long power = 1;

        for (unsigned int i = 0; i < digits; ++i) {
            if (digit != 0 && power > number / digit) {
                return false;
            }
            power *= digit;
        }

        if (power > number || sum > number - power) {
            return false;
        }

        sum += power;
        value /= 10;
    } while (value != 0);

    return sum == number;
}

static bool read_number(unsigned long long *number)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    if (number == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1) {
            free(input);
            return false;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 32;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return false;
                }
                new_capacity = capacity * 2;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return false;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return false;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        return false;
    }

    if (length + 1 > capacity) {
        char *new_input = realloc(input, length + 1);
        if (new_input == NULL) {
            free(input);
            return false;
        }
        input = new_input;
    }

    input[length] = '\0';

    char *start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        free(input);
        return false;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long value = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        return false;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return false;
    }

    *number = value;
    free(input);
    return true;
}

int main(void)
{
    unsigned long long number;

    if (!read_number(&number)) {
        return EXIT_FAILURE;
    }

    if (is_armstrong(number)) {
        printf("%llu is an Armstrong number.\n", number);
    } else {
        printf("%llu is not an Armstrong number.\n", number);
    }

    return EXIT_SUCCESS;
}
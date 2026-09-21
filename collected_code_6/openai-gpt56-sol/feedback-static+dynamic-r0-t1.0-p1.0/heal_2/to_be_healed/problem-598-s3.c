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
        const unsigned long long digit = value % 10;
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

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    char *end;
    unsigned long long number;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = capacity == 0 ? 2 : capacity + 1;
        char *new_input = realloc(input, new_capacity);

        if (new_input == NULL) {
            free(input);
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

    end = input;
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '-') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(end, &end, 10);

    if (errno == ERANGE) {
        free(input);
        return EXIT_FAILURE;
    }

    if (end == input || !isdigit((unsigned char)input[
            (size_t)(end - input) - 1])) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (is_armstrong(number)) {
        printf("%llu is an Armstrong number.\n", number);
    } else {
        printf("%llu is not an Armstrong number.\n", number);
    }

    return EXIT_SUCCESS;
}
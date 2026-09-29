#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <stdint.h>

static int has_odd_divisor_count(unsigned long long number)
{
    unsigned long long low = 1;
    unsigned long long high = number;

    while (low <= high) {
        unsigned long long middle = low + (high - low) / 2;
        unsigned long long quotient = number / middle;

        if (middle == quotient && number % middle == 0) {
            return 1;
        }

        if (middle > quotient) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *cursor;
    char *end;
    unsigned long long number;
    int ch;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
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

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    if (capacity <= length) {
        char *new_input;

        if (length == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        new_input = realloc(input, length + 1);
        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
    }

    input[length] = '\0';

    cursor = input;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(cursor, &end, 10);

    if (cursor == end || errno == ERANGE || number == 0) {
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

    puts(has_odd_divisor_count(number) ? "Odd" : "Even");

    free(input);
    return EXIT_SUCCESS;
}
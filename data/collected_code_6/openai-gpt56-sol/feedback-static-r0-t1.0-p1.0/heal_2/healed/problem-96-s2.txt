#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t count_divisors(uint64_t value)
{
    uint64_t count = 0;

    for (uint64_t divisor = 1; divisor <= value / divisor; ++divisor) {
        if (value % divisor == 0) {
            count += (divisor == value / divisor) ? UINT64_C(1) : UINT64_C(2);
        }
    }

    return count;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch = EOF;

    for (;;) {
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

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    new_capacity = SIZE_MAX;
                } else {
                    new_capacity = capacity * 2;
                }
            }

            if (new_capacity <= length + 1) {
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

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (capacity <= length) {
        char *new_input = realloc(input, length + 1);
        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }
        input = new_input;
    }

    input[length] = '\0';

    char *end = NULL;
    errno = 0;
    uintmax_t value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value == 0 ||
        value > UINT64_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIu64 "\n", count_divisors((uint64_t)value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
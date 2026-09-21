#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_demlo_number(uint64_t number)
{
    uint64_t square = number * number;
    uint64_t divisor = 1;

    while (divisor <= number / UINT64_C(10)) {
        divisor *= UINT64_C(10);
    }

    do {
        if (square % UINT64_C(10) !=
            (number / divisor) % UINT64_C(10)) {
            return 0;
        }

        square /= UINT64_C(10);
        divisor /= UINT64_C(10);
    } while (divisor != 0);

    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    char *end;
    uintmax_t value;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 32;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        char *resized;

        if (capacity == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        resized = realloc(input, capacity + 1);
        if (resized == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = resized;
    }

    input[length] = '\0';

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || value > UINT64_C(3037000499)) {
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_demlo_number((uint64_t)value)
             ? "Demlo number"
             : "Not a Demlo number");

    free(input);
    return EXIT_SUCCESS;
}
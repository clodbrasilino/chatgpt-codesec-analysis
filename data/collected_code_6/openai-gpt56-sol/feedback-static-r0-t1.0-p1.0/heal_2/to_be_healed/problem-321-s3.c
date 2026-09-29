#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int is_demlo_number(unsigned long long number)
{
    unsigned long long square = 0;
    unsigned long long increment = 1;

    while (square < number) {
        if (square > ULLONG_MAX - increment) {
            return 0;
        }

        square += increment;

        if (increment > ULLONG_MAX - 2ULL) {
            return 0;
        }

        increment += 2ULL;
    }

    if (square != number) {
        return 0;
    }

    do {
        if (number % 10ULL != 1ULL) {
            return 0;
        }

        number /= 10ULL;

        if (number == 0ULL) {
            return 1;
        }

        while (number % 10ULL == 2ULL) {
            number /= 10ULL;
        }

        if (number == 0ULL) {
            return 0;
        }
    } while (number % 10ULL == 1ULL);

    return 0;
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
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 32;
            } else {
                if (capacity > (SIZE_MAX - 1) / 2) {
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

    if (ch == EOF && length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        char *new_input;

        if (capacity == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        new_input = realloc(input, capacity + 1);
        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
    }

    input[length] = '\0';

    errno = 0;
    end = NULL;
    number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
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

    printf("%s\n",
           is_demlo_number(number) ? "Demlo number" : "Not a Demlo number");

    free(input);
    return EXIT_SUCCESS;
}
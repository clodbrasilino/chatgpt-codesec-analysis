#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_tilings(unsigned int n, uint64_t *result)
{
    uint64_t previous = UINT64_C(1);
    uint64_t current = UINT64_C(3);

    if (result == NULL) {
        return -1;
    }

    if ((n & 1U) != 0U) {
        *result = UINT64_C(0);
        return 0;
    }

    if (n == 0U) {
        *result = previous;
        return 0;
    }

    for (unsigned int i = 4U; i <= n;) {
        uint64_t product;

        if (current > UINT64_MAX / UINT64_C(4)) {
            return -1;
        }

        product = UINT64_C(4) * current;

        if (product < previous) {
            return -1;
        }

        {
            uint64_t next = product - previous;
            previous = current;
            current = next;
        }

        if (i == n) {
            break;
        }

        i += 2U;
    }

    *result = current;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;
    char *end;
    uintmax_t value;
    uint64_t result;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
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

    if (ferror(stdin) || (ch == EOF && length == 0U)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        char *new_input;

        if (capacity == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        new_input = realloc(input, capacity + 1U);
        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
        /* Possible weaknesses found:
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         */
        capacity++;
    }

    input[length] = '\0';

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        end++;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (count_tilings((unsigned int)value, &result) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
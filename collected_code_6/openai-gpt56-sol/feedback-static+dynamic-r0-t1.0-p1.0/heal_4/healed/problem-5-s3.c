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
        *result = UINT64_C(1);
        return 0;
    }

    for (unsigned int i = 4U; i <= n;) {
        uint64_t next;

        if (current > UINT64_MAX / UINT64_C(4)) {
            return -1;
        }

        next = UINT64_C(4) * current;

        if (next < previous) {
            return -1;
        }

        next -= previous;
        previous = current;
        current = next;

        if (i > n - 2U) {
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
    char *end = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    unsigned long value;
    uint64_t result;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1U) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2U;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0U)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX - 2U) {
        free(input);
        return EXIT_FAILURE;
    }

    if (capacity - length < 2U) {
        char *temporary = realloc(input, length + 2U);

        if (temporary == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = temporary;
    }

    input[length++] = '\n';
    input[length] = '\0';

    errno = 0;
    value = strtoul(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT_MAX) {
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

    if (count_tilings((unsigned int)value, &result) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
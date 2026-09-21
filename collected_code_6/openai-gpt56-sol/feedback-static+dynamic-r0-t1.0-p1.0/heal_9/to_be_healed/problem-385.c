#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int perrin(unsigned int n, uint64_t *result)
{
    uint64_t p0 = UINT64_C(3);
    uint64_t p1 = UINT64_C(0);
    uint64_t p2 = UINT64_C(2);

    if (result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = p0;
        return 1;
    }

    if (n == 1U) {
        *result = p1;
        return 1;
    }

    if (n == 2U) {
        *result = p2;
        return 1;
    }

    for (unsigned int i = 3U; i <= n; ++i) {
        uint64_t next;

        if (p0 > UINT64_MAX - p1) {
            return 0;
        }

        next = p0 + p1;
        p0 = p1;
        p1 = p2;
        p2 = next;
    }

    *result = p2;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    char *end = NULL;
    unsigned long value;
    uint64_t result;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;

        if (length == SIZE_MAX - 1U) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 32U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
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

    if (ferror(stdin) || length == 0U) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length + 1U > capacity) {
        char *resized = realloc(input, length + 1U);

        if (resized == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = resized;
    }

    input[length] = '\0';

    errno = 0;
    value = strtoul(input, &end, 10);

    if (errno == ERANGE || end == input || *end != '\0' ||
        value > UINT_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (!perrin((unsigned int)value, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
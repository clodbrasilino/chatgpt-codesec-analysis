#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        if (current > UINT64_MAX / UINT64_C(4)) {
            return -1;
        }

        uint64_t product = UINT64_C(4) * current;

        if (product < previous) {
            return -1;
        }

        uint64_t next = product - previous;
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
    char input[64];
    char *end = NULL;
    unsigned long value;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoul(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT_MAX) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (count_tilings((unsigned int)value, &result) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
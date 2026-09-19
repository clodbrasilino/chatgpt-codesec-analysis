#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int perrin(unsigned int n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = UINT64_C(3);
        return 1;
    }

    if (n == 1U) {
        *result = UINT64_C(0);
        return 1;
    }

    if (n == 2U) {
        *result = UINT64_C(2);
        return 1;
    }

    if (!perrin(n - 2U, &a) || !perrin(n - 3U, &b)) {
        return 0;
    }

    if (a > UINT64_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

int main(void)
{
    char input[64];
    char *end;
    unsigned long value;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoul(input, &end, 10);

    if (errno != 0 || end == input ||
        (*end != '\n' && *end != '\0') ||
        value > UINT_MAX) {
        return EXIT_FAILURE;
    }

    if (!perrin((unsigned int)value, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
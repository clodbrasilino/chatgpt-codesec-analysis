#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int find_nth_smart_number(uint64_t n, uint64_t *result)
{
    uint64_t values[3];
    uint64_t i2 = 0;
    uint64_t i3 = 0;
    uint64_t i5 = 0;

    if (n == 0 || result == NULL) {
        return 0;
    }

    uint64_t *smart = malloc((size_t)n * sizeof(*smart));
    if (smart == NULL) {
        return 0;
    }

    smart[0] = 1;

    for (uint64_t i = 1; i < n; ++i) {
        if (smart[i2] > UINT64_MAX / 2 ||
            smart[i3] > UINT64_MAX / 3 ||
            smart[i5] > UINT64_MAX / 5) {
            free(smart);
            return 0;
        }

        values[0] = smart[i2] * 2;
        values[1] = smart[i3] * 3;
        values[2] = smart[i5] * 5;

        uint64_t next = values[0];
        if (values[1] < next) {
            next = values[1];
        }
        if (values[2] < next) {
            next = values[2];
        }

        smart[i] = next;

        while (i2 <= i && smart[i2] <= next / 2) {
            ++i2;
        }
        while (i3 <= i && smart[i3] <= next / 3) {
            ++i3;
        }
        while (i5 <= i && smart[i5] <= next / 5) {
            ++i5;
        }
    }

    *result = smart[n - 1];
    free(smart);
    return 1;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed == 0 || parsed > UINT64_MAX ||
        parsed > SIZE_MAX / sizeof(uint64_t)) {
        return EXIT_FAILURE;
    }

    if (!find_nth_smart_number((uint64_t)parsed, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
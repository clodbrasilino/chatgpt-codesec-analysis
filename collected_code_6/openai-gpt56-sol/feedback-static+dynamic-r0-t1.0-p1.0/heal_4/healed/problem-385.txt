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
    char input[64];
    char *end;
    unsigned long value;
    uint64_t result;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    end = input;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end == '\n') {
        *end = '\0';
    } else {
        ch = fgetc(stdin);
        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            return EXIT_FAILURE;
        }

        if (ch == EOF && ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    if (input[0] == '\0') {
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoul(input, &end, 10);

    if (errno == ERANGE ||
        end == input ||
        *end != '\0' ||
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
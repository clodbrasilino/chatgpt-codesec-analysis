#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_factor_sum(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;
    uint64_t factor = 2;

    if (n == 0 || result == NULL) {
        return 0;
    }

    while (factor <= n / factor) {
        while (n % factor == 0) {
            if (sum > UINT64_MAX - factor) {
                return 0;
            }

            sum += factor;
            n /= factor;
        }

        factor = (factor == 2) ? 3 : factor + 2;
    }

    if (n > 1) {
        if (sum > UINT64_MAX - n) {
            return 0;
        }

        sum += n;
    }

    *result = sum;
    return 1;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t result;
    size_t length;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    length = 0;
    while (length < sizeof(input) && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof(input)) {
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed == 0 ||
        parsed > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (!minimum_factor_sum((uint64_t)parsed, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
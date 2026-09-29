#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
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
        uint64_t next;

        if (current > (UINT64_MAX + previous) / UINT64_C(4)) {
            return -1;
        }

        next = UINT64_C(4) * current - previous;
        previous = current;
        current = next;

        if (n - i < 2U) {
            break;
        }

        i += 2U;
    }

    *result = current;
    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    ssize_t length;
    char *end;
    uintmax_t value;
    uint64_t result;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[length - 1] = '\0';
    } else if (!feof(stdin)) {
        free(line);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(line, &end, 10);

    if (errno == ERANGE || end == line || value > UINT_MAX) {
        free(line);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return EXIT_FAILURE;
    }

    if (count_tilings((unsigned int)value, &result) != 0) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
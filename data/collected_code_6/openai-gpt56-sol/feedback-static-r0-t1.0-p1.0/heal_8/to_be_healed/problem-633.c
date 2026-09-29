#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { INPUT_BUFFER_SIZE = 256 };

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == EOF && ferror(stdin) ? -1 : 0;
}

static int read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[INPUT_BUFFER_SIZE];

    if (value == NULL) {
        return -1;
    }

    if (fgets(buffer, (int)sizeof buffer, stdin) == NULL) {
        return -1;
    }

    size_t length = 0;

    while (length < sizeof buffer && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length == sizeof buffer) {
        return -1;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (!feof(stdin)) {
        if (discard_line() != 0) {
            return -1;
        }
        return -1;
    }

    char *end = NULL;
    errno = 0;

    const uintmax_t parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed > UINT64_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

static int sum_pairwise_xor(const uint64_t *array, size_t length,
                            uint64_t *result)
{
    if (result == NULL || (length != 0 && array == NULL)) {
        return -1;
    }

#if SIZE_MAX > UINT64_MAX
    if (length > UINT64_MAX) {
        return -1;
    }
#endif

    const uint64_t count = (uint64_t)length;
    uint64_t sum = 0;

    for (unsigned int bit = 0; bit < 64; ++bit) {
        uint64_t ones = 0;

        for (size_t i = 0; i < length; ++i) {
            ones += (array[i] >> bit) & UINT64_C(1);
        }

        const uint64_t zeros = count - ones;

        if (ones != 0 && zeros > UINT64_MAX / ones) {
            return -1;
        }

        const uint64_t pairs = ones * zeros;

        if (pairs > (UINT64_MAX >> bit)) {
            return -1;
        }

        const uint64_t contribution = pairs << bit;

        if (sum > UINT64_MAX - contribution) {
            return -1;
        }

        sum += contribution;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    uint64_t input_length = 0;

    if (read_uint64(&input_length) != 0 ||
        input_length > SIZE_MAX ||
        input_length > SIZE_MAX / sizeof(uint64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    const size_t length = (size_t)input_length;
    uint64_t *array = NULL;

    if (length != 0) {
        array = calloc(length, sizeof *array);

        if (array == NULL) {
            fputs("Allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_uint64(&array[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    uint64_t result = 0;

    if (sum_pairwise_xor(array, length, &result) != 0) {
        fputs("Result overflow\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    free(array);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
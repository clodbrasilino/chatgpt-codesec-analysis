#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int parse_uint64(const char **text, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || *text == NULL || value == NULL) {
        return 0;
    }

    while (isspace((unsigned char)**text)) {
        ++*text;
    }

    if (**text == '\0' || **text == '-' || **text == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*text, &end, 10);

    if (end == *text || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *text = end;
    return 1;
}

static int read_uint64_pair(uint64_t *left, uint64_t *right)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    const char *cursor;
    size_t length;

    if (left == NULL || right == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (length < sizeof buffer && buffer[length] != '\0') {
        ++length;
    }

    if (length == sizeof buffer) {
        return 0;
    }

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[--length] = '\0';
        if (length > 0 && buffer[length - 1] == '\r') {
            buffer[length - 1] = '\0';
        }
    } else if (!feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return 0;
    }

    cursor = buffer;

    if (!parse_uint64(&cursor, left) || !parse_uint64(&cursor, right)) {
        return 0;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    return *cursor == '\0';
}

static int sum_even_naturals(uint64_t left, uint64_t right, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t factor1;
    uint64_t factor2;

    if (result == NULL || left == 0 || left > right) {
        return 0;
    }

    if ((left & UINT64_C(1)) != 0) {
        if (left == UINT64_MAX) {
            *result = 0;
            return 1;
        }
        first = left + UINT64_C(1);
    } else {
        first = left;
    }

    last = right - (right & UINT64_C(1));

    if (first > last) {
        *result = 0;
        return 1;
    }

    count = (last - first) / UINT64_C(2) + UINT64_C(1);

    if ((count & UINT64_C(1)) == 0) {
        factor1 = count / UINT64_C(2);
        factor2 = first + (last - first) / UINT64_C(2);
    } else {
        factor1 = count;
        factor2 = first / UINT64_C(2) + last / UINT64_C(2);
    }

    if (factor1 != 0 && factor2 > UINT64_MAX / factor1) {
        return 0;
    }

    *result = factor1 * factor2;
    return 1;
}

int main(void)
{
    uint64_t left;
    uint64_t right;
    uint64_t sum;

    if (!read_uint64_pair(&left, &right)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_even_naturals(left, right, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}